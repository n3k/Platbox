#pragma once
#include "Platbox.h"
#include "CbHooks.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, IrpCloseHandler)
#pragma alloc_text(PAGE, IrpCreateHandler)
#pragma alloc_text(PAGE, IrpUnloadHandler)
#pragma alloc_text(PAGE, IrpDeviceIoCtlHandler)
#pragma alloc_text(PAGE, IrpNotImplementedHandler)

#endif


NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) {
	UINT32 i = 0;
	PDEVICE_OBJECT DeviceObject = NULL;
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	UNICODE_STRING DeviceName, DosDeviceName = { 0 };

	UNREFERENCED_PARAMETER(RegistryPath);
	PAGED_CODE();

	RtlInitUnicodeString(&DeviceName, L"\\Device\\PlatboxDev");
	RtlInitUnicodeString(&DosDeviceName, L"\\DosDevices\\PlatboxDev");

	// Create the device
	Status = IoCreateDevice(DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&DeviceObject);

	if (!NT_SUCCESS(Status)) {
		// Delete the device
		IoDeleteDevice(DriverObject->DeviceObject);

		DbgPrint("[-] Error during IoCreateDevice...\n");
		return Status;
	}

	// Assign the IRP handlers
	for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++) {
		// Disable the Compiler Warning: 28169
#pragma warning(push)
#pragma warning(disable : 28169)
		DriverObject->MajorFunction[i] = IrpNotImplementedHandler;
#pragma warning(pop)
	}

	// Assign the IRP handlers for Create, Close and Device Control
	DriverObject->MajorFunction[IRP_MJ_CREATE] = IrpCreateHandler;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = IrpCloseHandler;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IrpDeviceIoCtlHandler;

	// Assign the driver Unload routine
	DriverObject->DriverUnload = IrpUnloadHandler;

	// Set the flags
	DeviceObject->Flags |= DO_BUFFERED_IO;
	DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	// Create the symbolic link
	Status = IoCreateSymbolicLink(&DosDeviceName, &DeviceName);


	DbgPrint("[+] PlatboxDrv loaded!\n");

	return Status;
}

NTSTATUS IrpCreateHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) {
	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(DeviceObject);
	PAGED_CODE();

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS IrpCloseHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) {
	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(DeviceObject);
	PAGED_CODE();

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

VOID IrpUnloadHandler(IN PDRIVER_OBJECT DriverObject) {
	UNICODE_STRING DosDeviceName = { 0 };

	PAGED_CODE();

	RtlInitUnicodeString(&DosDeviceName, L"\\DosDevices\\PlatboxDev");

	// Delete the symbolic link
	IoDeleteSymbolicLink(&DosDeviceName);

	// Delete the device
	IoDeleteDevice(DriverObject->DeviceObject);

	DbgPrint("[-] PlatboxDrv Unloaded\n");
}

NTSTATUS IrpNotImplementedHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) {
	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;

	UNREFERENCED_PARAMETER(DeviceObject);
	PAGED_CODE();

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_NOT_SUPPORTED;
}


NTSTATUS IrpDeviceIoCtlHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) {
	ULONG IoControlCode = 0;
	PIO_STACK_LOCATION IrpSp = NULL;
	NTSTATUS Status = STATUS_NOT_SUPPORTED;

	UNREFERENCED_PARAMETER(DeviceObject);
	PAGED_CODE();

	IrpSp = IoGetCurrentIrpStackLocation(Irp);
	IoControlCode = IrpSp->Parameters.DeviceIoControl.IoControlCode;
	//__debugbreak();
	if (IrpSp) {
		switch (IoControlCode) {
		case IOCTL_ISSUE_SW_SMI:
			Status = SendSWSmiHandler(Irp, IrpSp);
			break;
		case IOCTL_EXECUTE_SHELLCODE:
			Status = ExecuteShellcodeHandler(Irp, IrpSp);
			break;
		case IOCTL_READ_PCI_HEADER:
			Status = ReadPCIHeaderHandler(Irp, IrpSp);
			break;
		case IOCTL_READ_PCI_BYTE:
			Status = ReadPCIByte(Irp, IrpSp);
			break;
		case IOCTL_READ_PCI_WORD:
			Status = ReadPCIWord(Irp, IrpSp);
			break;
		case IOCTL_READ_PCI_DWORD:
			Status = ReadPCIDword(Irp, IrpSp);
			break;
		case IOCTL_WRITE_PCI_BYTE:
			Status = WritePCIByte(Irp, IrpSp);
			break;
		case IOCTL_WRITE_PCI_WORD:
			Status = WritePCIWord(Irp, IrpSp);
			break;
		case IOCTL_WRITE_PCI_DWORD:
			Status = WritePCIDword(Irp, IrpSp);
			break;
		case IOCTL_GET_PCI_BAR_SIZE:
			Status = ReadPCIBarSize(Irp, IrpSp);
			break;
		case IOCTL_READ_PHYSICAL_MEM:
			Status = ReadPhysicalMemory(Irp, IrpSp);
			break;
		case IOCTL_WRITE_PHYSICAL_MEM:
			Status = WritePhysicalMemory(Irp, IrpSp);
			break;
		case IOCTL_READ_MSR:
			Status = ReadMSR(Irp, IrpSp);
			break;
		case IOCTL_WRITE_MSR:
			Status = WriteMSR(Irp, IrpSp);
			break;
		case IOCTL_PATCH_CALLBACK:
			Status = PatchCallback(Irp, IrpSp);
			break;
		case IOCTL_RESTORE_CALLBACK:
			Status = RestoreCallback(Irp, IrpSp);
			break;
		case IOCTL_REMOVE_ALL_CALLBACKS_HOOKS:
			Status = RemoveAllCallbackHooks(Irp, IrpSp);
			break;
		default:
			DbgPrint("[-] Invalid IOCTL Code: 0x%X\n", IoControlCode);
			Status = STATUS_INVALID_DEVICE_REQUEST;
			Irp->IoStatus.Information = 0;
			break;
		}
	}

	Irp->IoStatus.Status = Status;
	//Irp->IoStatus.Information = 0;
	// Complete the request
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;
}


#pragma auto_inline(off)


NTSTATUS SendSWSmiHandler(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength == sizeof(SW_SMI_CALL)) {
		PSW_SMI_CALL s = (PSW_SMI_CALL) Irp->AssociatedIrp.SystemBuffer;
		UINT16 b2b3 = ((s->SwSmiData << 8) | s->SwSmiNumber);
		__try
		{
			_swsmi(b2b3, s->rax, s->rbx, s->rcx, s->rdx, s->rsi, s->rdi);
			Status = STATUS_SUCCESS;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			Status = GetExceptionCode();
		}	
	}	
	Irp->IoStatus.Information = 0;
	return Status;
}

NTSTATUS ExecuteShellcodeHandler(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	UINT32 inputLen = IrpSp->Parameters.DeviceIoControl.InputBufferLength;
	if (inputLen > 0) {
		PVOID code_region = ExAllocatePool(
			NonPagedPoolExecute,
			inputLen);
		memmove(code_region, Irp->AssociatedIrp.SystemBuffer, inputLen);
		((void(*)(void))code_region)();
		ExFreePool(code_region);
		Status = STATUS_SUCCESS;

	}

	Irp->IoStatus.Information = 0;
	return Status;
}

NTSTATUS ReadPCIHeaderHandler(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();
	
	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_PCI_CONFIGURATION_SPACE_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= 256) {
			PREAD_PCI_CONFIGURATION_SPACE_CALL p = (PREAD_PCI_CONFIGURATION_SPACE_CALL)Irp->AssociatedIrp.SystemBuffer;
			UINT8 bus = p->bus;
			UINT8 device = p->device;
			UINT8 function = p->function;
			memset(Irp->AssociatedIrp.SystemBuffer, 0x00, 256);
			_read_pci_compatible_configuration_space(bus, device, function, Irp->AssociatedIrp.SystemBuffer);
			Irp->IoStatus.Information = 256;
			Status = STATUS_SUCCESS;
		}
	}
		
	return Status;
}

NTSTATUS ReadPCIByte(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_PCI_DATA_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= 1) {
			PREAD_PCI_DATA_CALL p = (PREAD_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
			UINT32 bus = p->bus;
			UINT32 device = p->device;
			UINT32 function = p->function;
			UINT32 offset = p->offset;
			UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
			memset(Irp->AssociatedIrp.SystemBuffer, 0x00, IrpSp->Parameters.DeviceIoControl.OutputBufferLength);
			_read_pci_byte(CF8, Irp->AssociatedIrp.SystemBuffer);
			Irp->IoStatus.Information = 1;
			Status = STATUS_SUCCESS;
		}
	}

	return Status;
}

NTSTATUS ReadPCIWord(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_PCI_DATA_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= 2) {
			PREAD_PCI_DATA_CALL p = (PREAD_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
			UINT32 bus = p->bus;
			UINT32 device = p->device;
			UINT32 function = p->function;
			UINT32 offset = p->offset;
			UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
			memset(Irp->AssociatedIrp.SystemBuffer, 0x00, IrpSp->Parameters.DeviceIoControl.OutputBufferLength);
			_read_pci_word(CF8, Irp->AssociatedIrp.SystemBuffer);
			Irp->IoStatus.Information = 2;
			Status = STATUS_SUCCESS;
		}
	}

	return Status;
}

NTSTATUS ReadPCIDword(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_PCI_DATA_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= 4) {
			PREAD_PCI_DATA_CALL p = (PREAD_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
			UINT32 bus = p->bus;
			UINT32 device = p->device;
			UINT32 function = p->function;
			UINT32 offset = p->offset;
			UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
			memset(Irp->AssociatedIrp.SystemBuffer, 0x00, IrpSp->Parameters.DeviceIoControl.OutputBufferLength);
			_read_pci_dword(CF8, Irp->AssociatedIrp.SystemBuffer);
			Irp->IoStatus.Information = 4;
			Status = STATUS_SUCCESS;
		}
	}

	return Status;
}

NTSTATUS WritePCIByte(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(WRITE_PCI_DATA_CALL)) {
		PWRITE_PCI_DATA_CALL p = (PWRITE_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
		UINT32 bus = p->bus;
		UINT32 device = p->device;
		UINT32 function = p->function;
		UINT32 offset = p->offset;
		UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
		__try {
			_write_pci_byte(CF8, p->value);
			Status = STATUS_SUCCESS;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {

		}
	}

	return Status;
}

NTSTATUS WritePCIWord(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(WRITE_PCI_DATA_CALL)) {
		PWRITE_PCI_DATA_CALL p = (PWRITE_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
		UINT32 bus = p->bus;
		UINT32 device = p->device;
		UINT32 function = p->function;
		UINT32 offset = p->offset;
		UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
		__try {
			_write_pci_word(CF8, p->value);
			Status = STATUS_SUCCESS;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {

		}
	}

	return Status;
}

NTSTATUS WritePCIDword(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(WRITE_PCI_DATA_CALL)) {		
		PWRITE_PCI_DATA_CALL p = (PWRITE_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
		UINT32 bus = p->bus;
		UINT32 device = p->device;
		UINT32 function = p->function;
		UINT32 offset = p->offset;
		UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
		__try {
			_write_pci_dword(CF8, p->value);
			Status = STATUS_SUCCESS;
		}
		__except(EXCEPTION_EXECUTE_HANDLER) {

		}
		
	}

	return Status;
}

NTSTATUS ReadPCIBarSize(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_PCI_DATA_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= sizeof(PVOID)) {
			PREAD_PCI_DATA_CALL p = (PREAD_PCI_DATA_CALL)Irp->AssociatedIrp.SystemBuffer;
			UINT32 bus = p->bus;
			UINT32 device = p->device;
			UINT32 function = p->function;
			UINT32 offset = p->offset;
			UINT32 CF8 = ((1 << 0x1F) | (bus << 0x10) | (device << 0xB) | (function << 0x08) | (offset << 2));
			memset(Irp->AssociatedIrp.SystemBuffer, 0x00, IrpSp->Parameters.DeviceIoControl.OutputBufferLength);
			_read_pci_bar_size(CF8, Irp->AssociatedIrp.SystemBuffer);
			Irp->IoStatus.Information = sizeof(PVOID);
			Status = STATUS_SUCCESS;
		}
	}

	return Status;
}

NTSTATUS ReadPhysicalMemory(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_PHYSICAL_MEM_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= 1) {
			UINT32 read_size = IrpSp->Parameters.DeviceIoControl.OutputBufferLength;
			PREAD_PHYSICAL_MEM_CALL p = (PREAD_PHYSICAL_MEM_CALL)Irp->AssociatedIrp.SystemBuffer;
			PVOID va = MmMapIoSpace(p->address, read_size, MmNonCached);
			if (va) {
				memmove(Irp->AssociatedIrp.SystemBuffer, va, read_size);
				MmUnmapIoSpace(va, read_size);
				Irp->IoStatus.Information = read_size;
				Status = STATUS_SUCCESS;
			}
		}
	}

	return Status;
}

NTSTATUS WritePhysicalMemory(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;

	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(WRITE_PHYSICAL_MEM_CALL)) {					
		PWRITE_PHYSICAL_MEM_CALL p = (PWRITE_PHYSICAL_MEM_CALL)Irp->AssociatedIrp.SystemBuffer;
		if (p->size <= sizeof(p->data)) {
			PVOID va = MmMapIoSpace(p->address, p->size, MmNonCached);
			if (va) {
				memmove(va, p->data, p->size);
				MmUnmapIoSpace(va, p->size);
				Status = STATUS_SUCCESS;
			}
		}			
	}

	return Status;
}

NTSTATUS ReadMSR(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;
	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(READ_MSR_CALL)) {
		if (IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= sizeof(DWORD64)) {
			PREAD_MSR_CALL p = (PREAD_MSR_CALL)Irp->AssociatedIrp.SystemBuffer;
			__try {
				_rdmsr(p->msr, Irp->AssociatedIrp.SystemBuffer);
				Irp->IoStatus.Information = sizeof(DWORD64);
				Status = STATUS_SUCCESS;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				*(DWORD64 *)Irp->AssociatedIrp.SystemBuffer = 0xFFFFFFFFFFFFFFFF;
				Irp->IoStatus.Information = sizeof(DWORD64);
				Status = STATUS_SUCCESS;
			}
		}
	}
	return Status;
}

NTSTATUS WriteMSR(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;
	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(WRITE_MSR_CALL)) {		
		PWRITE_MSR_CALL p = (PWRITE_MSR_CALL)Irp->AssociatedIrp.SystemBuffer;
		__try {
			_wrmsr(p->msr, p->value);
			Status = STATUS_SUCCESS;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			
		}
		
	}
	return Status;
}

NTSTATUS PatchCallback(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;
	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(PATCH_CALLBACK) 
		&& IrpSp->Parameters.DeviceIoControl.OutputBufferLength >= sizeof(PVOID) ) 
	{
		__try {
			PVOID hookCbAddress = CreateCbHook((PPATCH_CALLBACK)Irp->AssociatedIrp.SystemBuffer);
			if (hookCbAddress != NULL) {
				*((PVOID *)Irp->AssociatedIrp.SystemBuffer) = hookCbAddress;
				Irp->IoStatus.Information = sizeof(PVOID);
				Status = STATUS_SUCCESS;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {

		}

	}
	return Status;
}

NTSTATUS RestoreCallback(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;
	if (IrpSp->Parameters.DeviceIoControl.InputBufferLength >= sizeof(RESTORE_CALLBACK))
	{
		__try {
			RemoveCbHook((PRESTORE_CALLBACK)Irp->AssociatedIrp.SystemBuffer);			
			Status = STATUS_SUCCESS;			
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
	}
	return Status;
}

NTSTATUS RemoveAllCallbackHooks(IN PIRP Irp, IN PIO_STACK_LOCATION IrpSp) {
	NTSTATUS Status;
	UNREFERENCED_PARAMETER(Irp);
	PAGED_CODE();

	Irp->IoStatus.Information = 0;
	RemoveAllCbHooks();
	return STATUS_SUCCESS;
}


#pragma auto_inline()