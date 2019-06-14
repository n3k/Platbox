#include "PlatboxClient.h"


void EnumerateACPITables() {
	char Signature[4] = { 'U','E','F','I' };
	UINT32 requiredSize = EnumSystemFirmwareTables(0x49464555, NULL, 0);
	if (requiredSize == 0) {
		printf("Error in EnumSystemFirmwareTables: %08x\n", GetLastError());		
		return;
	}
	PVOID firmwareTablesBuffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, requiredSize);
	if (!firmwareTablesBuffer) {
		printf("- Error: allocation failed!\n");
		return;
	}
	requiredSize = EnumSystemFirmwareTables((DWORD)Signature, firmwareTablesBuffer, requiredSize);
	if (requiredSize == 0) {
		printf("Error in EnumSystemFirmwareTables\n");
		HeapFree(GetProcessHeap(), 0, firmwareTablesBuffer);
		return;
	}
	print_memory(0, (char *) firmwareTablesBuffer, requiredSize);

	HeapFree(GetProcessHeap(), 0, firmwareTablesBuffer);
}