#include "PlatboxClient.h"

#define PAGE_SIZE 0x1000

void read_physical_memory(HANDLE h, UINT64 address, UINT32 size, PVOID buffer, BOOL bPrint) {
	DWORD bytesReturned = 0;
	NTSTATUS status = -1;
	if (size > 0) {
		READ_PHYSICAL_MEM_CALL p = { 0 };		

		PVOID mem = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, PAGE_SIZE);
		if (!mem) {
			printf("-> Memory allocation failed!\n");
			return;
		}

		int i = 0;
		UINT32 auxSize = size;
		while (auxSize > PAGE_SIZE) {					
			p.address = address + (i * PAGE_SIZE);
			status = DeviceIoControl(h, IOCTL_READ_PHYSICAL_MEM,
				&p, sizeof(READ_PHYSICAL_MEM_CALL),
				mem, PAGE_SIZE, &bytesReturned, NULL);

			if (NT_SUCCESS(status)) {
				printf("-> %08x bytes read from physical memory %p\n", PAGE_SIZE, p.address);			
				if (buffer) {
					memcpy((char *)buffer + (i * PAGE_SIZE), mem, PAGE_SIZE);
				}
			}

			if (bPrint) {
				print_memory(p.address, (char *)mem, PAGE_SIZE);
			}
			auxSize = auxSize - PAGE_SIZE;
			i++;
		}
		
		p.address = address + (i * PAGE_SIZE);
		status = DeviceIoControl(h, IOCTL_READ_PHYSICAL_MEM,
		&p, sizeof(READ_PHYSICAL_MEM_CALL),
		mem, auxSize, &bytesReturned, NULL);

		if (NT_SUCCESS(status)) {
			printf("-> %08x bytes read from physical Memory %p\n", auxSize, p.address);
			if (bPrint) {
				print_memory(p.address, (char *)mem, auxSize);
			}
			if (buffer) {
				memcpy((char *)buffer + (i * PAGE_SIZE), mem, auxSize);
			}
		}					

		HeapFree(GetProcessHeap(), 0, mem);
	}
}

void read_physical_memory_into_file(HANDLE h, UINT64 address, UINT32 size, char *filename) {

	char filepath[2048] = { 0 };
	GetCurrentDirectoryA(sizeof(filepath), filepath);
	strcat(filepath, "\\");
	strcat(filepath, filename);
	FILE *f = fopen(filename, "wb");
	DWORD bytesReturned = 0;
	NTSTATUS status = -1;

	if (size > 0) {
		READ_PHYSICAL_MEM_CALL p = { 0 };

		PVOID mem = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, PAGE_SIZE);
		if (!mem) {
			printf("-> Memory allocation failed!\n");
			return;
		}

		int i = 0;
		UINT32 auxSize = size;
		while (auxSize > PAGE_SIZE) {
			p.address = address + (i * PAGE_SIZE);
			status = DeviceIoControl(h, IOCTL_READ_PHYSICAL_MEM,
				&p, sizeof(READ_PHYSICAL_MEM_CALL),
				mem, PAGE_SIZE, &bytesReturned, NULL);

			if (NT_SUCCESS(status)) {
				printf("-> %08x bytes read from physical memory %p\n", PAGE_SIZE, p.address);
				fwrite(mem, PAGE_SIZE, 1, f);
			}		
			auxSize = auxSize - PAGE_SIZE;
			i++;
		}

		p.address = address + (i * PAGE_SIZE);
		status = DeviceIoControl(h, IOCTL_READ_PHYSICAL_MEM,
			&p, sizeof(READ_PHYSICAL_MEM_CALL),
			mem, auxSize, &bytesReturned, NULL);

		if (NT_SUCCESS(status)) {
			printf("-> %08x bytes read from physical Memory %p\n", auxSize, p.address);
			fwrite(mem, auxSize, 1, f);
		}

		HeapFree(GetProcessHeap(), 0, mem);
	}
	fclose(f);
}

void write_byte_physical_memory(HANDLE h, UINT64 address, UINT32 value) {
	WRITE_PHYSICAL_MEM_CALL p = { 0 };
	p.address = address;
	p.data[0] = value;
	p.size = 1;

	DWORD bytesReturned = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_PHYSICAL_MEM,
		&p, sizeof(READ_PHYSICAL_MEM_CALL),
		0, 0, &bytesReturned, NULL);

	if (NT_SUCCESS(status)) {
		printf("-> 1 byte written to physical address %p\n", address);
	}
}

void parse_handle_physmem_operation(HANDLE h, int argc, char **argv) {
	// physmem r 0x000000 0x100--> reads 0x100 bytes from physical address 0
	if (!strcmp(argv[1], "r")) {
		if (argc == 4) {
			UINT64 address = strtoul(argv[2], NULL, 16);
			UINT32 size = strtoul(argv[3], NULL, 16);
			read_physical_memory(h, address, size, NULL, TRUE);
		}
		if (argc == 5) {
			// physmem r 0xFFAA0000 0x100 weird_region.bin
			UINT64 address = strtoul(argv[2], NULL, 16);
			UINT32 size = strtoul(argv[3], NULL, 16);
			read_physical_memory_into_file(h, address, size, argv[4]);
		}
	}
	if (!strcmp(argv[1], "wb")) {
		if (argc == 4) {
			UINT64 address = strtoul(argv[2], NULL, 16);
			UINT32 value = strtoul(argv[3], NULL, 16);
			write_byte_physical_memory(h, address, value);
		}
	}
}