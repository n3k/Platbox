#include "PlatboxClient.h"

void read_msr(HANDLE h, int argc, char **argv) {
	/* rdmsr <msr> */
	if (argc == 2) {
		READ_MSR_CALL msr_call = { 0 };
		msr_call.msr = strtoul(argv[1], NULL, 16);
		UINT64 result = 0;
		DWORD bytesReturned = 0;
		NTSTATUS status = DeviceIoControl(h, IOCTL_READ_MSR,
			&msr_call, sizeof(READ_MSR_CALL),
			&result, sizeof(UINT64),
			&bytesReturned, NULL);
		if (NT_SUCCESS(status)) {
			printf("-> MSR %08x: %p\n", msr_call.msr, result);
		}
		else {
			printf("-> Failed reading MSR: %08x\n", msr_call.msr);
		}
	}
}

void write_msr(HANDLE h, int argc, char **argv) {
	/* wrmsr <msr> <value> */
	if (argc == 3) {
		WRITE_MSR_CALL msr_call = { 0 };
		msr_call.msr = strtoul(argv[1], NULL, 16);
		msr_call.value = strtoul(argv[1], NULL, 16);
		UINT64 result = 0;
		DWORD bytesReturned = 0;
		NTSTATUS status = DeviceIoControl(h, IOCTL_READ_MSR,
			&msr_call, sizeof(WRITE_MSR_CALL),
			&result, sizeof(UINT64),
			&bytesReturned, NULL);
		if (NT_SUCCESS(status)) {
			printf("-> Attempted to write %p into MSR %p\n", msr_call.value, msr_call.msr);
		}
	}
}

void check_smm_msr_feature_control(HANDLE h) {
	READ_MSR_CALL msr_call = { 0 };
	DWORD bytesReturned = 0;

	msr_call.msr = MSR_SMM_FEATURE_CONTROL;
	UINT64 smm_feature_control = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_MSR,
		&msr_call, sizeof(READ_MSR_CALL),
		&smm_feature_control, sizeof(UINT64),
		&bytesReturned, NULL);

	printf("-> MSR_SMM_FEATURE_CONTROL (4E0h): %p\n", smm_feature_control);
	if (smm_feature_control & 1) {
		printf("    -> LOCKED\n");
	}
	else {
		printf("    -> UNLOCKED\n");
	}
	if (smm_feature_control & 4) {
		printf("    -> SMM_Code_Chk_En: TRUE\n");
	}
	else {
		printf("    -> SMM_Code_Chk_En: FALSE\n");
	}
}

void check_ia32_msr_feature_control(HANDLE h) {
	/*
	If the lock bit (bit 0) isn't set, then
	IA32_SMRR_PHYSBASE_MSR and IA32_SMRR_PHYSMASK_MSR
	can be changed.
	If the Lock bit is set then those can only be changed while in SMM
	*/
	READ_MSR_CALL msr_call = { 0 };
	DWORD bytesReturned = 0;

	msr_call.msr = IA32_FEATURE_CONTROL;
	UINT64 msr_feature_control = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_MSR,
		&msr_call, sizeof(READ_MSR_CALL),
		&msr_feature_control, sizeof(UINT64),
		&bytesReturned, NULL);

	printf("-> MSR_FEATURE_CONTROL (3Ah): %p\n", msr_feature_control);
	if (msr_feature_control & 1) {
		printf("    -> LOCKED\n");
	}
	else {
		printf("    -> UNLOCKED\n");
	}
	if (msr_feature_control & 4) {
		printf("    -> SMRR Enabled: TRUE\n");
	}
	else {
		printf("    -> SMRR Enabled: FALSE\n");
	}
}

void check_memory_lock_msr(HANDLE h) {
	/*
	If the lock bit (bit 0) isn't set, then
	IOBAS and IOLIM registers can change
	*/
	READ_MSR_CALL msr_call = { 0 };
	DWORD bytesReturned = 0;

	msr_call.msr = LT_MEMORY_LOCK_MSR;
	UINT64 mt_lock_msr = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_MSR,
		&msr_call, sizeof(READ_MSR_CALL),
		&mt_lock_msr, sizeof(UINT64),
		&bytesReturned, NULL);

	printf("-> LT_MEMORY_LOCK_MSR (2E7h): %p\n", mt_lock_msr);
	if (mt_lock_msr & 1) {
		printf("    -> LOCKED\n");
	}
	else {
		printf("    -> UNLOCKED\n");
	}
}

void get_smrr(HANDLE h, UINT32 *out_smrambase, UINT32 *out_smramsize) {
	READ_MSR_CALL msr_call = { 0 };
	DWORD bytesReturned = 0;

	msr_call.msr = IA32_SMRR_PHYSBASE_MSR;
	UINT64 smrr_physbase = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_MSR,
		&msr_call, sizeof(READ_MSR_CALL),
		&smrr_physbase, sizeof(UINT64),
		&bytesReturned, NULL);

	msr_call.msr = IA32_SMRR_PHYSMASK_MSR;
	UINT64 smrrmask = 0;
	status = DeviceIoControl(h, IOCTL_READ_MSR,
		&msr_call, sizeof(READ_MSR_CALL),
		&smrrmask, sizeof(UINT64),
		&bytesReturned, NULL);

	UINT32 smram_base = smrr_physbase & smrrmask;
	UINT32 smram_size = ((~smrrmask) & 0xFFFFFFFF) + 1;
	UINT32 smram_limit = smram_base + smram_size - 1;
	if (NT_SUCCESS(status)) {
		printf("-> IA32_SMRR_PHYSBASE_MSR: %08x\n", smrr_physbase);
		printf("-> IA32_SMRR_PHYSMASK_MSR: %08x\n", smrrmask);
		printf("-> SMRAM base: %08x\n", smram_base);
		printf("-> SMRAM size: %08x\n", smram_size);
		printf("-> SMRAM limit: %08x\n", smram_limit);
		if (out_smrambase != NULL)
			*out_smrambase = smram_base;
		if (out_smramsize != NULL)
			*out_smramsize = smram_size;
	}
	else {
		printf("-> Failed reading MSR: %08x\n", msr_call.msr);
	}
}