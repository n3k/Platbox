// Written by Enrique Nissim (IOActive) 06/2018

#include "UEFIVars.h"

const char * UEFI_VARIABLE_ATTRIBUTES[] = {
	"NV", //"NON_VOLATILE", 
	"BS", //"BOOTSERVICE_ACCESS", 
	"RT", //RUNTIME_ACCESS",
	"HR", //"HARDWARE_ERROR_RECORD",
	"AW", //"AUTHENTICATED_WRITE_ACCESS", 
	"TA", //"TIME_BASED_AUTHENTICATED_WRITE_ACCESS",
	"AW", //"APPEND_WRITE",
};

void display_variable_attributes(DWORD attributes) {
	int i;
	for (i = 0; i < ARRAYSIZE(UEFI_VARIABLE_ATTRIBUTES); i++)
		if ((1 << i) & attributes)
			printf("%s|", UEFI_VARIABLE_ATTRIBUTES[i]);
}


void display_guid(GUID *guid) {
	printf("{%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3],
		guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]);
}

NTSTATUS enable_privilege(ULONG privId)
{
	ULONG previousState;
	NTSTATUS status = RtlAdjustPrivilege(privId, TRUE, FALSE, &previousState);
	if (NT_SUCCESS(status))
		printf("Privilege \'%u\' OK\n", privId);
	else printf("RtlAdjustPrivilege (%u) %08x\n", privId, status);
	return status;
}

void get_more_privileges(void) {
	enable_privilege(SE_SYSTEM_ENVIRONMENT);
	//enable_privilege(SE_LOAD_DRIVER);
	//enable_privilege(SE_SECURITY);
	//enable_privilege(SE_TCB);
	//enable_privilege(SE_BACKUP);
	//enable_privilege(SE_RESTORE);
	//enable_privilege(SE_DEBUG);
}

void list_unprotected_variables(PVARIABLE_NAME_AND_VALUE buffer) {
	for (; buffer; buffer = buffer->NextEntryOffset ? (PVARIABLE_NAME_AND_VALUE)((PBYTE)buffer + buffer->NextEntryOffset) : NULL)
	{
		if (buffer->Attributes & EFI_VARIABLE_RUNTIME_ACCESS &&
			buffer->Attributes & EFI_VARIABLE_NON_VOLATILE &&
			!(buffer->Attributes & EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS) &&
			!(buffer->Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
			)
		{
			printf("\n%S", buffer->Name);
			display_guid(&buffer->VendorGuid);
			printf("|");
			display_variable_attributes(buffer->Attributes);
		}
	}
	printf("\n");
}

void list_all(PVARIABLE_NAME_AND_VALUE buffer) {
	for (; buffer; buffer = buffer->NextEntryOffset ? (PVARIABLE_NAME_AND_VALUE)((PBYTE)buffer + buffer->NextEntryOffset) : NULL)
	{
		printf("\n%S", buffer->Name);
		//puts("VendorGUID: "); 
		display_guid(&buffer->VendorGuid);
		printf("|");
		//printf("\nAttributes: %08x\n", buffer->Attributes);					
		display_variable_attributes(buffer->Attributes);
		//puts("\n");
		//printf("\nLength of Data: %08x\n", buffer->ValueLength);
		//if (buffer->ValueLength && buffer->ValueOffset) {
		//	print_memory(0x00, ((char *)buffer + buffer->ValueOffset), buffer->ValueLength);
		//}
	}
}

void list_uefi_variables()
{
	HMODULE ntdll = LoadLibraryA("ntdll.dll");
	NtEnumerateSystemEnvironmentValuesEx = (_NtEnumerateSystemEnvironmentValuesEx)
		GetProcAddress(ntdll, "NtEnumerateSystemEnvironmentValuesEx");
	printf("NtEnumerateSystemEnvironmentValuesEx: %p\n", NtEnumerateSystemEnvironmentValuesEx);

	RtlAdjustPrivilege = (_RtlAdjustPrivilege)
		GetProcAddress(ntdll, "RtlAdjustPrivilege");
	printf("RtlAdjustPrivilege: %p\n", RtlAdjustPrivilege);

	PVARIABLE_NAME_AND_VALUE buffer = NULL;
	DWORD bufferLen = 0;
	NTSTATUS status;

	get_more_privileges();

	status = NtEnumerateSystemEnvironmentValuesEx(VARIABLE_INFORMATION_VALUES, NULL, &bufferLen);
	if (status == 0xC0000061) {
		printf("Not enough privileges!\n");
	}

	if ((status == STATUS_BUFFER_TOO_SMALL) && bufferLen)
	{
		if (buffer = (PVARIABLE_NAME_AND_VALUE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, bufferLen))
		{
			status = NtEnumerateSystemEnvironmentValuesEx(VARIABLE_INFORMATION_VALUES, buffer, &bufferLen);
			if (NT_SUCCESS(status))
			{
				list_unprotected_variables(buffer);
			}
			else {
				printf("\nError: \n", GetLastError());
			}
		}
		if (buffer) {
			HeapFree(GetProcessHeap(), 0, buffer);
		}
	}
}