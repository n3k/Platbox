// Written by Enrique Nissim (IOActive) 06/2018

#pragma once

#pragma once
extern "C" {
#include "DeltaFuzz.h"
}

#include <windows.h>
#include <intrin.h>


#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

#define IOCTL_ISSUE_SW_SMI  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_EXECUTE_SHELLCODE  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_PCI_HEADER  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_PCI_BYTE  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_PCI_WORD  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_PCI_DWORD  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PCI_BYTE  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PCI_WORD  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PCI_DWORD  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_PCI_BAR_SIZE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x809, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_PHYSICAL_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80A, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PHYSICAL_MEM CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80B, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_MSR CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80C, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_WRITE_MSR CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80D, METHOD_BUFFERED, FILE_ANY_ACCESS)

/* Utils */
void print_memory(unsigned long address, char *buffer, unsigned int bytes_to_print);
void get_user_input(char *input, int size);
char **parse_arguments(char *command_line, char arg_delim);

/* UEFI Vars */ 
void list_uefi_variables();

/* Acpi dump */
void EnumerateACPITables();

/* MSR */
void read_msr(HANDLE h, int argc, char **argv);
void write_msr(HANDLE h, int argc, char **argv);
void get_smrr(HANDLE h, UINT32 *out_smrambase, UINT32 *out_smramsize);
void check_smm_msr_feature_control(HANDLE h);
void check_ia32_msr_feature_control(HANDLE h);
void check_memory_lock_msr(HANDLE h);


// Functions
void read_pci_header(HANDLE h, UINT8 bus, UINT8 device, UINT8 function);
BYTE read_pci_byte(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset);
WORD read_pci_word(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset);
DWORD read_pci_dword(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset);
void write_pci_byte(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset, UINT value);
void write_pci_word(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset, UINT value);
void write_pci_dword(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset, UINT value);
void read_pci_bar_info(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset);
void parse_bus_device_function(char *line, UINT *bus, UINT *device, UINT *function);
void parse_handle_pci_operation(HANDLE h, int argc, char **argv);

// Hostbridge operations
void read_hostbridge_pxpepbar(HANDLE h, DWORD64 *pPxpepbar);
void read_hostbridge_mchbar(HANDLE h, DWORD64 *pMchbar);
void read_hostbridge_gmch(HANDLE h, WORD *pGmch);
void read_hostbridge_deven(HANDLE h, DWORD *pDeven);
void read_hostbridge_pavpc(HANDLE h, DWORD *pPavpc);
void read_hostbridge_dpr(HANDLE h, DWORD *pDpr);
void read_hostbridge_pciexbar(HANDLE h, DWORD64 *pPciexbar);
void read_hostbridge_dmibar(HANDLE h, DWORD64 *pDmibar);
void read_hostbridge_meseg_base(HANDLE h, DWORD64 *pMsegBase);
void read_hostbridge_meseg_limit(HANDLE h, DWORD64 *pMsegLimit);
void read_hostbridge_smramc(HANDLE h, BYTE *pSmramc);
void read_hostbridge_remap_base(HANDLE h, DWORD64 *pRemapBase);
void read_hostbridge_remap_limit(HANDLE h, DWORD64 *pRemapLimit);
void read_hostbridge_tom(HANDLE h, DWORD64 *pTom);
void read_hostbridge_touud(HANDLE h, DWORD64 *pTouud);
void read_hostbridge_bdsm(HANDLE h, DWORD *pBdsm);
void read_hostbridge_bgsm(HANDLE h, DWORD *pBgsm);
void read_hostbridge_tseg(HANDLE h, DWORD *pTseg);
void read_hostbridge_tolud(HANDLE h, DWORD *pTolud);
void get_chipset_id(HANDLE h, WORD *platformVID, WORD *platformDID, WORD *PCHVID, WORD *PCHDID);
void print_pxpepbar(DWORD64 *p);
void print_mchbar(DWORD64 *p);
void print_gmch(WORD *p);
void print_deven(DWORD *p);
void print_pavpc(DWORD *p);
void print_dpr(DWORD *p);
void print_pciexbar(DWORD64 *p);
void print_dmibar(DWORD64 *p);
void print_mesegbase(DWORD64 *p);
void print_meseglimit(DWORD64 *p);
void print_smramc(BYTE *p);
void print_remapbase(DWORD64 *p);
void print_remaplimit(DWORD64 *p);
void print_tom(DWORD64 *p);
void print_touud(DWORD64 *p);
void print_bdsm(DWORD *p);
void print_bgsm(DWORD *p);
void print_tsegmb(DWORD *p);
void print_tolud(DWORD *p);

// ACPI Operations
void read_pmc_acpi_base_address(HANDLE h, DWORD *pAcpiBase);
void print_pmc_acpi_base_address(DWORD *p);
void read_pmc_acpi_control(HANDLE h, DWORD *pAcpiControl);
void print_pmc_acpi_control(DWORD *p);
void read_pmc_pm_base_address(HANDLE h, DWORD *pPmBaseAddress);
void print_pmc_pm_base_address(DWORD *p);

// SPI Interface Operations
void read_spi_interface_bios_decode_enable(HANDLE h, DWORD *pBiosSpiBDE);
void print_spi_interface_bios_decode_enable(DWORD *p);
void read_spi_interface_bar0_mmio(HANDLE h, DWORD *pBar0Mmio);
void print_spi_interface_bar0_mmio(DWORD *p);
void read_spi_interface_bios_control(HANDLE h, DWORD *pBiosCtl);
void print_spi_interface_bios_control(DWORD *p);

// SPIBAR Operations
void print_spi_bar_bios_bfpreg(DWORD *p);
void read_spi_bar_bios_bfpreg(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_hsfs_ctl(DWORD *p);
void read_spi_bar_hsfs_ctl(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_faddr(DWORD *p);
void read_spi_bar_faddr(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_dlock(DWORD *p);
void read_spi_bar_dlock(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_freg0(DWORD *p);
void read_spi_bar_freg0(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_freg1(DWORD *p);
void read_spi_bar_freg1(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_freg2(DWORD *p);
void read_spi_bar_freg2(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_freg3(DWORD *p);
void read_spi_bar_freg3(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_freg4(DWORD *p);
void read_spi_bar_freg4(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_freg5(DWORD *p);
void read_spi_bar_freg5(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_fpr0(DWORD *p);
void read_spi_bar_fpr0(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_fpr1(DWORD *p);
void read_spi_bar_fpr1(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_fpr2(DWORD *p);
void read_spi_bar_fpr2(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_fpr3(DWORD *p);
void read_spi_bar_fpr3(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);
void print_spi_bar_fpr4(DWORD *p);
void read_spi_bar_fpr4(HANDLE h, DWORD64 SPIBAR, DWORD *pOut);

/* physmem */

void read_physical_memory(HANDLE h, UINT64 address, UINT32 size, PVOID buffer, BOOL bPrint);
void write_byte_physical_memory(HANDLE h, UINT64 address, UINT32 value);
void read_physical_memory_into_file(HANDLE h, UINT64 address, UINT32 size, char *filename);
void parse_handle_physmem_operation(HANDLE h, int argc, char **argv);



typedef struct _SW_SMI_CALL {
	UINT8 SwSmiNumber; // 0xb2
	UINT8 SwSmiData; // 0xb3
	UINT64 rax;
	UINT64 rbx;
	UINT64 rcx;
	UINT64 rdx;
	UINT64 rsi;
	UINT64 rdi;
} SW_SMI_CALL, *PSW_SMI_CALL;

typedef struct _READ_PCI_CONFIGURATION_SPACE_CALL {
	UINT8 bus;
	UINT8 device;
	UINT8 function;
} READ_PCI_CONFIGURATION_SPACE_CALL, *PREAD_PCI_CONFIGURATION_SPACE_CALL;

typedef struct _READ_PCI_DATA_CALL {
	UINT8 bus;
	UINT8 device;
	UINT8 function;
	UINT8 offset;
} READ_PCI_DATA_CALL, *PREAD_PCI_DATA_CALL;

typedef struct _WRITE_PCI_DATA_CALL {
	UINT8 bus;
	UINT8 device;
	UINT8 function;
	UINT8 offset;
	UINT32 value;
} WRITE_PCI_DATA_CALL, *PWRITE_PCI_DATA_CALL;

typedef struct _READ_PHYSICAL_MEM_CALL {
	UINT64 address;
} READ_PHYSICAL_MEM_CALL, *PREAD_PHYSICAL_MEM_CALL;

typedef struct _WRITE_PHYSICAL_MEM_CALL {
	UINT64 address;
	UINT32 size;
	UCHAR data[0x1000];
} WRITE_PHYSICAL_MEM_CALL, *PWRITE_PHYSICAL_MEM_CALL;

typedef struct _READ_MSR_CALL {
	UINT32 msr;
} READ_MSR_CALL, *PREAD_MSR_CALL;

typedef struct _WRITE_MSR_CALL {
	UINT32 msr;
	UINT64 value;
} WRITE_MSR_CALL, *PWRITE_MSR_CALL;


typedef struct _PCI_CONFIG_ADDRESS {
	DWORD Alignment : 2;
	DWORD RegisterNumber : 6;
	DWORD FunctionNumber : 3;
	DWORD DeviceNumber : 5;
	DWORD BusNumber : 8;
	DWORD Reserved : 7;
	DWORD Enabled : 1;
} PCI_CONFIG_ADDRESS;

typedef struct _PCI_BAR {
	DWORD IOMapped : 1;
	DWORD _64Bit : 2;
	DWORD Prefetchable : 1;
	DWORD BaseAddress : 28;
} PCI_BAR, *PPCI_BAR;

typedef struct _PCI_CONFIG_HEADER {
	WORD DeviceId;
	WORD VendorId;
	WORD Status;
	WORD Command;
	DWORD ClassCode : 24;
	DWORD RevisionId : 8;
	BYTE BIST;
	BYTE HeaderType;
	BYTE LatencyTimer;
	BYTE CacheLineSize;
	PCI_BAR BAR0;
	PCI_BAR BAR1;
	PCI_BAR BAR2;
	PCI_BAR BAR3;
	PCI_BAR BAR4;
	PCI_BAR BAR5;
	DWORD CardbusCISPointer;
	WORD SubsystemId;
	WORD SubsystemVendorId;
	DWORD ExpansionROMBaseAddress;
	DWORD Reversed0 : 24;
	DWORD CapabilitiesPointer : 8;
	DWORD Reserved1;
	BYTE MaxLat;
	BYTE MinGnt;
	BYTE InterruptPin;
	BYTE InterruptLine;
} PCI_CONFIG_HEADER, *PPCI_CONFIG_HEADER;

typedef enum {
	GeneralDevice,
	PCI2PCIBridge,
	CardBusBridge
} PCI_HEADER_TYPE;

typedef struct {
	DWORD64 PXPEPBAREN : 1;
	DWORD64 Rsvd0 : 11;
	DWORD64 PXPEPBAR : 27;
	DWORD64 Rsvd1 : 25;
} _PEXPEPBAR;

typedef struct {
	DWORD64 MCHBAREN : 1;
	DWORD64 Rsvd0 : 14;
	DWORD64 MCHBAR : 24;
	DWORD64 Rsvd1 : 25;
} _MCHBAR;

typedef struct {
	WORD GGCLCK : 1; // Lock all bits in the register
	WORD IVD : 1;  // 0 -> Enable Device 2 (integrated graphics) / 1 -> Disable
	WORD VAMEN : 1;
	WORD Rsvd0 : 3;
	WORD GGMS : 2;
	WORD GMS : 8;
} _GMCH;

typedef struct {
	DWORD D0EN : 1;
	DWORD D1F2EN : 1;
	DWORD D1F1EN : 1;
	DWORD D1F0EN : 1;
	DWORD D2EN : 1;
	DWORD D3EN : 1;
	DWORD Rsvd0 : 2;
	DWORD D4EN : 1;
	DWORD Rsvd1 : 2;
	DWORD D5EN : 1;
	DWORD Rsvd2 : 2;
	DWORD D7EN : 1;
	DWORD D8EN : 1;
	DWORD Rsvd3 : 16;
} _DEVEN;

typedef struct {
	DWORD PCME : 1; // Protected Content Memory Enabled?
	DWORD PAVPE : 1; // 0 Disabled / 1 Enabled
	DWORD PAVPLCK : 1;
	DWORD HVYMODSEL : 1;
	DWORD OVTATTACK : 1;
	DWORD Rsvd0 : 1;
	DWORD ASMFEN : 1;
	DWORD Rsvd1 : 13;
	DWORD PCMBASE : 12; // This is locked when PAVPE = 1
} _PAVPC;

typedef struct {
	DWORD LOCK : 1;
	DWORD PRS : 1;
	DWORD EPM : 1;
	DWORD Rsvd0 : 1;
	DWORD DPRSIZE : 8;
	DWORD Rsvd1 : 8;
	DWORD TopOfDPR : 12;
} _DPR;

typedef struct {
	DWORD64 PCIEXBAREN : 1;
	DWORD64 LENGTH : 2;
	DWORD64 Rsvd0 : 23;
	DWORD64 ADMSK64 : 1;
	DWORD64 ADMSK128 : 1;
	DWORD64 PCIEXBAR : 11;
	DWORD64 Rsvd1 : 25;
} _PCIEXBAR;

typedef struct { // Root Complex Register Range Base Address
	DWORD64 DMIBAREN : 1;
	DWORD64 Rsvd0 : 11;
	DWORD64 DMIBAR : 27;
	DWORD64 Rsvd1 : 30;
} _DMIBAR;

typedef struct {
	DWORD64 Rsvd0 : 20;
	DWORD64 MEBASE : 19;
	DWORD64 Rsvd1 : 25;
} _MESEG_BASE;

typedef struct {
	DWORD64 Rsvd0 : 10;
	DWORD64 MELCK : 1;
	DWORD64 ME_STLEN_EN : 1;
	DWORD64 Rsvd1 : 8;
	DWORD64 MEMASK : 19;
	DWORD64 Rsvd2 : 25;
} _MESEG_LIMIT;

typedef struct {
	BYTE C_BASE_SEG : 3;
	BYTE G_SMRAME : 1;
	BYTE D_LCK : 1;
	BYTE D_CLS : 1;
	BYTE D_OPEN : 1;
	BYTE Rsvd0 : 1;
} _SMRAMC;

typedef struct {
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 REMAPBASE : 19;
	DWORD64 Rsvd1 : 25;
} _REMAPBASE;

typedef struct {
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 REMAPLMT : 19;
	DWORD64 Rsvd1 : 25;
} _REMAPLIMIT;

typedef struct { // Top Of Memory (TOM)
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 TOM : 19;
	DWORD64 Rsvd1 : 25;
} _TOM;

typedef struct { // Top Of Upper Usable DRAM
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 TOUUD : 19;
	DWORD64 Rsvd1 : 25;
} _TOUUD;

typedef struct {
	DWORD LOCK : 1;
	DWORD Rsvd0 : 19;
	DWORD BDSM : 12;
} _BDSM;

typedef struct {
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 BGSM : 12;
} _BGSM;

typedef struct {
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 TSEGMB : 19;
} _TSEGMB;

typedef struct {
	DWORD64 LOCK : 1;
	DWORD64 Rsvd0 : 19;
	DWORD64 TOLUD : 19;
} _TOLUD;

// ACPI B0:F31:D2

typedef struct {
	DWORD STYPE : 1;
	DWORD Rsvd0 : 7;
	DWORD BA : 24;
} _ABASE;

typedef struct {
	DWORD SCIS : 3;
	DWORD Rsvd0 : 4;
	DWORD EN : 1;
	DWORD PWRM_EN : 1;
	DWORD Rsvd1 : 23;
} _ACTL;

typedef struct {
	DWORD STYPE : 1;
	DWORD Rsvd0 : 7;
	DWORD BA : 24;
} _PWRMBASE;

// SPI INTERFACE B0:F31:D5

typedef struct {
	DWORD E40 : 1;
	DWORD E50 : 1;
	DWORD E60 : 1;
	DWORD E70 : 1;
	DWORD Rsvd0 : 2;
	DWORD LEE : 1;
	DWORD LFE : 1;
	DWORD EC0 : 1;
	DWORD EC8 : 1;
	DWORD ED0 : 1;
	DWORD ED8 : 1;
	DWORD EE0 : 1;
	DWORD EE8 : 1;
	DWORD EF0 : 1;
	DWORD EF8 : 1;
	DWORD Rsvd1 : 16;
} _BIOS_SPI_BDE;

typedef struct {
	DWORD WPD : 1;
	DWORD LE : 1;
	DWORD SRC : 2;
	DWORD TSS : 1;
	DWORD EISS : 1;
	DWORD BBS : 1;
	DWORD BILD : 1;
	DWORD SPI_SYNC_SS : 1;
	DWORD OSFH : 1;
	DWORD SPI_ASYNC_SS : 1;
	DWORD ASE_BWP : 1;
} _BIOS_SPI_BC;

// SPI BAR

typedef struct {
	DWORD PRB : 15;
	DWORD Rsvd0 : 1;
	DWORD PRL : 15;
	DWORD Rsvd1 : 1;
} _BIOS_BFPREG;

typedef struct {
	DWORD FDONE : 1;
	DWORD FCERR : 1;
	DWORD H_AEL : 1;
	DWORD Rsvd0 : 2;
	DWORD H_SCPI : 1;
	DWORD Rsvd1 : 5;
	DWORD WRSDIS : 1;
	DWORD PRR34_LOCKDN : 1;
	DWORD FDOPSS : 1;
	DWORD FDV : 1;
	DWORD FLOCKDN : 1;
	DWORD FGO : 1;
	DWORD FCYCLE : 4;
	DWORD WET : 1;
	DWORD Rsvd2 : 2;
	DWORD FDBC : 6;
	DWORD Rsvd3 : 1;
	DWORD FSMIE : 1;	
} _BIOS_HSFSTS_CTL;

typedef struct {
	DWORD FLA : 27;
	DWORD Rsvd : 5;
} _BIOS_FADDR ;

typedef struct {
	DWORD BMWAGLOCKDN : 1;
	DWORD BMRAGLOCKDN : 1;
	DWORD SBMWAGLOCKDN : 1;
	DWORD SBMRAGLOCKDN : 1;
	DWORD SPARE7 : 1;
	DWORD SPARE6 : 1;
	DWORD SPARE5 : 1;
	DWORD SPARE4 : 1;
	DWORD PR0LOCKDN : 1;
	DWORD PR1LOCKDN : 1;
	DWORD PR2LOCKDN : 1;
	DWORD PR3LOCKDN : 1;
	DWORD PR4LOCKDN : 1;
	DWORD SPARE3 : 1;
	DWORD SPARE2 : 1;
	DWORD SPARE1 : 1;
	DWORD SSEQLOCKDN : 1;
	DWORD Rsvd0 : 15;
} _BIOS_DLOCK;

typedef struct {
	DWORD RB : 15;
	DWORD Rsvd0 : 1;
	DWORD RL : 15;
	DWORD Rsvd1 : 1;
} _BIOS_FREG;

typedef struct {
	DWORD PRB : 15;
	DWORD RPE : 1;
	DWORD PRL : 15;
	DWORD WPE : 1;
} _BIOS_FPR;

#define IA32_FEATURE_CONTROL 0x3A
#define STAR_MSR 0xC0000081
#define LSTAR_MSR 0xC0000082
#define CSTAR_MSR 0xC0000083
#define SFMASK_MSR 0xC0000084
#define IA32_SMRR_PHYSBASE_MSR 0x1F2
#define IA32_SMRR_PHYSMASK_MSR 0x1F3
#define LT_MEMORY_LOCK_MSR 0x2e7
#define MSR_SMM_FEATURE_CONTROL 0x4E0
#define MSR_BOOTGUARD 0x13A