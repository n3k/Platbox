// Written by Enrique Nissim (IOActive) 06/2018

#include "platboxclient.h"

//////////////////////////////////////////////////////
// SPI Memory Mapped Resgisters (SPIBAR)

void print_spi_bar_bios_bfpreg(DWORD *p) {
	printf("SPIBAR::_BIOS_BFPREG - SPI BIOS MMIO PRI (BIOS_BFPREG) - Offset 0h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PRB (BIOS Flash Primary Region Base): %08x\n", ((_BIOS_BFPREG *)p)->PRB << 12);
	printf("   -> PRL (BIOS Flash Primary Region Limit): %08x\n", ((_BIOS_BFPREG *)p)->PRL << 12);
}
void read_spi_bar_bios_bfpreg(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// SPI BIOS MMIO PRI (BIOS_BFPREG) - Offset 0h
	DWORD offset = 0;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}

void print_spi_bar_hsfs_ctl(DWORD *p) {
	printf("SPIBAR::_BIOS_HSFSTS_CTL - Hardware Sequencing Flash Status and Control (BIOS_HSFSTS_CTL) - Offset 4h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> FDONE (Flash Cycle Done): %02x\n", ((_BIOS_HSFSTS_CTL *)p)->FDONE);
	printf("   -> WRSDIS (Flash Configuration Lock-Down): %02x\n", ((_BIOS_HSFSTS_CTL *)p)->WRSDIS);
	printf("   -> PRR34_LOCKDN (PRR3 PRR4 Lock-Down): %02x\n", ((_BIOS_HSFSTS_CTL *)p)->PRR34_LOCKDN);
	printf("   -> FLOCKDN (Flash Configuration Lock-Down): %02x\n", ((_BIOS_HSFSTS_CTL *)p)->FLOCKDN);
}
void read_spi_bar_hsfs_ctl(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Hardware Sequencing Flash Status and Control (BIOS_HSFSTS_CTL) - Offset 4h
	DWORD offset = 4;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}

void print_spi_bar_faddr(DWORD *p) {
	printf("SPIBAR::_BIOS_FADDR - Flash Address (BIOS_FADDR) - Offset 8h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> FLA (Flash Linear Address): %08x\n", ((_BIOS_FADDR *)p)->FLA);
}
void read_spi_bar_faddr(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Address (BIOS_FADDR) - Offset 8h
	DWORD offset = 8;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}

void print_spi_bar_dlock(DWORD *p) {
	printf("SPIBAR::_BIOS_DLOCK - Discrete Lock Bits (BIOS_DLOCK) - Offset Ch\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> BMWAGLOCKDN (BMWAG Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->BMWAGLOCKDN);
	printf("   -> BMRAGLOCKDN (BMRAG Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->BMRAGLOCKDN);
	printf("   -> SBMWAGLOCKDN (SBMWAGLOCKDN Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->SBMWAGLOCKDN);
	printf("   -> SBMRAGLOCKDN (SBMRAGLOCKDN Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->SBMRAGLOCKDN);
	printf("   -> PR0LOCKDN (PR0 Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->PR0LOCKDN);
	printf("   -> PR1LOCKDN (PR1 Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->PR1LOCKDN);
	printf("   -> PR2LOCKDN (PR2 Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->PR2LOCKDN);
	printf("   -> PR3LOCKDN (PR3 Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->PR3LOCKDN);
	printf("   -> PR4LOCKDN (PR4 Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->PR4LOCKDN);
	printf("   -> SSEQLOCKDN (SSEQ Lock-Down): %02x\n", ((_BIOS_DLOCK *)p)->SSEQLOCKDN);
}
void read_spi_bar_dlock(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Discrete Lock Bits (BIOS_DLOCK) - Offset Ch
	DWORD offset = 0xC;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}

void print_spi_bar_freg0(DWORD *p) {
	printf("SPIBAR::_BIOS_FREG0 - Flash Region 0 (BIOS_FREG0) - Offset 54h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> RB (Region Base): %08x\n", ((_BIOS_FREG *)p)->RB<<12);
	printf("   -> RL (Region Limit): %08x\n", ((_BIOS_FREG *)p)->RL << 12);
}
void read_spi_bar_freg0(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Region 0 (BIOS_FREG0) - Offset 54h
	DWORD offset = 0x54;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_freg1(DWORD *p) {
	printf("SPIBAR::_BIOS_FREG1 - Flash Region 1 (BIOS_FREG1) - Offset 58h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> RB (Region Base): %08x\n", ((_BIOS_FREG *)p)->RB << 12);
	printf("   -> RL (Region Limit): %08x\n", ((_BIOS_FREG *)p)->RL << 12);
}
void read_spi_bar_freg1(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Region 1 (BIOS_FREG1) - Offset 58h
	DWORD offset = 0x58;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_freg2(DWORD *p) {
	printf("SPIBAR::_BIOS_FREG2 - Flash Region 2 (BIOS_FREG2) - Offset 5Ch\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> RB (Region Base): %08x\n", ((_BIOS_FREG *)p)->RB << 12);
	printf("   -> RL (Region Limit): %08x\n", ((_BIOS_FREG *)p)->RL << 12);
}
void read_spi_bar_freg2(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Region 2 (BIOS_FREG2) - Offset 5Ch
	DWORD offset = 0x5C;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_freg3(DWORD *p) {
	printf("SPIBAR::_BIOS_FREG3 - Flash Region 3 (BIOS_FREG3) - Offset 60h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> RB (Region Base): %08x\n", ((_BIOS_FREG *)p)->RB << 12);
	printf("   -> RL (Region Limit): %08x\n", ((_BIOS_FREG *)p)->RL << 12);
}
void read_spi_bar_freg3(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Region 3 (BIOS_FREG3) - Offset 60h
	DWORD offset = 0x60;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_freg4(DWORD *p) {
	printf("SPIBAR::_BIOS_FREG4 - Flash Region 4 (BIOS_FREG4) - Offset 64h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> RB (Region Base): %08x\n", ((_BIOS_FREG *)p)->RB << 12);
	printf("   -> RL (Region Limit): %08x\n", ((_BIOS_FREG *)p)->RL << 12);
}
void read_spi_bar_freg4(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Region 4 (BIOS_FREG4) - Offset 64h
	DWORD offset = 0x64;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_freg5(DWORD *p) {
	printf("SPIBAR::_BIOS_FREG5 - Flash Region 5 (BIOS_FREG5) - Offset 68h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> RB (Region Base): %08x\n", ((_BIOS_FREG *)p)->RB << 12);
	printf("   -> RL (Region Limit): %08x\n", ((_BIOS_FREG *)p)->RL << 12);
}
void read_spi_bar_freg5(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Region 5 (BIOS_FREG5) - Offset 68h
	DWORD offset = 0x68;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}

void print_spi_bar_fpr0(DWORD *p) {
	printf("SPIBAR::_BIOS_FPR0 - Flash Protected Range 0 (BIOS_FPR0) - Offset 84h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PRB (Protected Range Base): %08x\n", ((_BIOS_FPR *)p)->PRB << 12);
	printf("   -> PRL (Protected Range Limit): %08x\n", ((_BIOS_FPR *)p)->PRL << 12);
	printf("   -> RPE (Read Protection Enable): %s\n", ((_BIOS_FPR *)p)->RPE ? "TRUE" : "FALSE");
	printf("   -> WPE (Write Protection Enable): %s\n", ((_BIOS_FPR *)p)->WPE ? "TRUE" : "FALSE");
}
void read_spi_bar_fpr0(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Protected Range 0 (BIOS_FPR0) - Offset 84h
	DWORD offset = 0x84;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_fpr1(DWORD *p) {
	printf("SPIBAR::_BIOS_FPR1 - Flash Protected Range 1 (BIOS_FPR1) - Offset 88h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PRB (Protected Range Base): %08x\n", ((_BIOS_FPR *)p)->PRB << 12);
	printf("   -> PRL (Protected Range Limit): %08x\n", ((_BIOS_FPR *)p)->PRL << 12);
	printf("   -> RPE (Read Protection Enable): %s\n", ((_BIOS_FPR *)p)->RPE ? "TRUE" : "FALSE");
	printf("   -> WPE (Write Protection Enable): %s\n", ((_BIOS_FPR *)p)->WPE ? "TRUE" : "FALSE");
}
void read_spi_bar_fpr1(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Protected Range 1 (BIOS_FPR1) - Offset 88h
	DWORD offset = 0x88;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_fpr2(DWORD *p) {
	printf("SPIBAR::_BIOS_FPR2 - Flash Protected Range 2 (BIOS_FPR2) - Offset 8Ch\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PRB (Protected Range Base): %08x\n", ((_BIOS_FPR *)p)->PRB << 12);
	printf("   -> PRL (Protected Range Limit): %08x\n", ((_BIOS_FPR *)p)->PRL << 12);
	printf("   -> RPE (Read Protection Enable): %s\n", ((_BIOS_FPR *)p)->RPE ? "TRUE" : "FALSE");
	printf("   -> WPE (Write Protection Enable): %s\n", ((_BIOS_FPR *)p)->WPE ? "TRUE" : "FALSE");
}
void read_spi_bar_fpr2(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Protected Range 2 (BIOS_FPR2) - Offset 8Ch
	DWORD offset = 0x8C;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_fpr3(DWORD *p) {
	printf("SPIBAR::_BIOS_FPR3 - Flash Protected Range 3 (BIOS_FPR3) - Offset 90h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PRB (Protected Range Base): %08x\n", ((_BIOS_FPR *)p)->PRB << 12);
	printf("   -> PRL (Protected Range Limit): %08x\n", ((_BIOS_FPR *)p)->PRL << 12);
	printf("   -> RPE (Read Protection Enable): %s\n", ((_BIOS_FPR *)p)->RPE ? "TRUE" : "FALSE");
	printf("   -> WPE (Write Protection Enable): %s\n", ((_BIOS_FPR *)p)->WPE ? "TRUE" : "FALSE");
}
void read_spi_bar_fpr3(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Protected Range 3 (BIOS_FPR3) - Offset 90h
	DWORD offset = 0x90;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}
void print_spi_bar_fpr4(DWORD *p) {
	printf("SPIBAR::_BIOS_FPR4 - Flash Protected Range 4 (BIOS_FPR4) - Offset 94h\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PRB (Protected Range Base): %08x\n", ((_BIOS_FPR *)p)->PRB << 12);
	printf("   -> PRL (Protected Range Limit): %08x\n", ((_BIOS_FPR *)p)->PRL << 12);
	printf("   -> RPE (Read Protection Enable): %s\n", ((_BIOS_FPR *)p)->RPE ? "TRUE" : "FALSE");
	printf("   -> WPE (Write Protection Enable): %s\n", ((_BIOS_FPR *)p)->WPE ? "TRUE" : "FALSE");
}
void read_spi_bar_fpr4(HANDLE h, DWORD64 SPIBAR, DWORD *pOut) {
	// Flash Protected Range 4 (BIOS_FPR4) - Offset 94h
	DWORD offset = 0x94;
	read_physical_memory(h, SPIBAR + offset, 4, pOut, FALSE);
}

//////////////////////////////////////////////////////
// SPI Interface B0:D31:F5 Registers

void print_spi_interface_bar0_mmio(DWORD *p) {
	printf("0:31:5_BIOS_SPI_BAR0 - SPI BAR0 MMIO (BIOS_SPI_BAR0)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> SPI BAR: %08x\n", ((PCI_BAR *)p)->BaseAddress << 4);
	printf("   -> I/O Space: %s\n", ((PCI_BAR *)p)->IOMapped ? "TRUE" : "FALSE");
}
void read_spi_interface_bar0_mmio(HANDLE h, DWORD *pBar0Mmio) {
	// SPI BAR0 MMIO (BIOS_SPI_BAR0)
	UINT32 offset1 = 0x10;
	*pBar0Mmio = read_pci_dword(h, 0, 31, 5, offset1 / 4);
}

void print_spi_interface_bios_decode_enable(DWORD *p) {
	printf("0:31:5_BIOS_SPI_BDE - BIOS Decode Enable (BIOS_SPI_BDE)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> E40 (40-4F Enable) 1MB FF400000h-FF4FFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->E40 ? "TRUE" : "FALSE");
	printf("   -> E50 (50-5F Enable) 1MB FF500000h-FF5FFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->E50 ? "TRUE" : "FALSE");
	printf("   -> E60 (60-6F Enable) 1MB FF600000h-FF6FFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->E60 ? "TRUE" : "FALSE");
	printf("   -> E70 (70-7F Enable) 1MB FF700000h-FF7FFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->E70 ? "TRUE" : "FALSE");
	printf("   -> LEE (Legacy E Segment Enable) 64K E0000h-EFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->LEE ? "TRUE" : "FALSE");
	printf("   -> LFE (Legacy F Segment Enable) 64K F0000h-FFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->LFE ? "TRUE" : "FALSE");
	printf("   -> EC0 (C0-C7 Enable) 512K FFC00000h-FFC7FFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->EC0 ? "TRUE" : "FALSE");
	printf("   -> EC8 (C8-CF Enable) 512K FFC80000h-FFCFFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->EC8 ? "TRUE" : "FALSE");
	printf("   -> ED0 (D0-D7 Enable) 512K FFD00000h-FFD7FFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->ED0 ? "TRUE" : "FALSE");
	printf("   -> ED8 (D8-DF Enable) 512K FFD80000h-FFDFFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->ED8 ? "TRUE" : "FALSE");
	printf("   -> EE0 (E0-E7 Enable) 512K FFE00000h-FFE7FFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->EE0 ? "TRUE" : "FALSE");
	printf("   -> EE8 (E8-EF Enable) 512K FFE80000h-FFEFFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->EE8 ? "TRUE" : "FALSE");
	printf("   -> EF0 (F0-F7 Enable) 512K FFF00000h-FFF7FFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->EF0 ? "TRUE" : "FALSE");
	printf("   -> EF8 (F8-FF Enable) 512K FFF80000h-FFFFFFFFh: %s\n", ((_BIOS_SPI_BDE *)p)->EF8 ? "TRUE" : "FALSE");
}
void read_spi_interface_bios_decode_enable(HANDLE h, DWORD *pBiosSpiBDE) {
	// BIOS Decode Enable (BIOS_SPI_BDE)
	UINT32 offset1 = 0xD8;
	*pBiosSpiBDE = read_pci_dword(h, 0, 31, 5, offset1 / 4);
}

void print_spi_interface_bios_control(DWORD *p) {
	printf("0:31:5_BIOS_SPI_BC - BIOS Control (BIOS_SPI_BC) - Offset DCh\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> WPD (Write Protect Disable):  %s\n", ((_BIOS_SPI_BC *)p)->WPD ? "TRUE" : "FALSE");
	printf("   -> LE (BIOS Lock Enable): %s\n", ((_BIOS_SPI_BC *)p)->LE ? "TRUE" : "FALSE");
	printf("   -> SRC (SPI Read Configuration): %02x\n", ((_BIOS_SPI_BC *)p)->SRC);
	printf("   -> TSS (Top Swap Status): %02x\n", ((_BIOS_SPI_BC *)p)->TSS);
	printf("   -> EISS (Enable InSMM.STS): %s\n", ((_BIOS_SPI_BC *)p)->EISS ? "TRUE" : "FALSE");
	// BBS determines the destination of accesses to the BIOS memory range.
	// Cannot be changed if BILD is set
	printf("   -> BBS (Boot BIOS Strap): %s\n", ((_BIOS_SPI_BC *)p)->BBS ? "LPC" : "SPI");
	printf("   -> BILD (BIOS Interface Lock-Down): %s\n", ((_BIOS_SPI_BC *)p)->BILD ? "TRUE" : "FALSE");
	printf("   -> OSFH (OS Function Hide): %s\n", ((_BIOS_SPI_BC *)p)->OSFH ? "TRUE" : "FALSE");
	printf("   -> ASE_BWP (Async SMI Enable for BIOS Write Protection): %s\n", ((_BIOS_SPI_BC *)p)->ASE_BWP ? "TRUE" : "FALSE");
}
void read_spi_interface_bios_control(HANDLE h, DWORD *pBiosCtl) {
	// 
	UINT32 offset1 = 0xDC;
	*pBiosCtl = read_pci_dword(h, 0, 31, 5, offset1 / 4);
}

//////////////////////////////////////////////////////
// POWER MANAGEMENT / ACPI Registers B0:F31:D2


void print_pmc_acpi_base_address(DWORD *p) {
	printf("0:31:2_ABASE - ACPI Base Address (ABASE)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> ACPI BAR: %08x\n", ((_ABASE *)p)->BA << 8);
	printf("   -> I/O Space: %s\n", ((_ABASE *)p)->STYPE ? "TRUE" : "FALSE");
}
void read_pmc_acpi_base_address(HANDLE h, DWORD *pAcpiBase) {
	// ACPI Base Address (ABASE)
	UINT32 offset1 = 0x40;
	*pAcpiBase = read_pci_dword(h, 0, 31, 2, offset1 / 4);
}

void print_pmc_acpi_control(DWORD *p) {
	printf("0:31:2_ACTL - ACPI Control (ACTL)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> ACPI Enable: %s\n", ((_ACTL *)p)->EN ? "TRUE" : "FALSE");
	printf("   -> PWRM Enable: %s\n", ((_ACTL *)p)->PWRM_EN ? "TRUE" : "FALSE");
}
void read_pmc_acpi_control(HANDLE h, DWORD *pAcpiControl) {
	// ACPI Control (ACTL)
	UINT32 offset1 = 0x44;
	*pAcpiControl = read_pci_dword(h, 0, 31, 2, offset1 / 4);
}

void print_pmc_pm_base_address(DWORD *p) {
	printf("0:31:2_PWRMBASE - PM Base Address (PWRMBASE)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PWRMBASE: %08xh\n", ((_PWRMBASE *)p)->BA << 8);
	printf("   -> I/O Space: %s\n", ((_PWRMBASE *)p)->STYPE ? "TRUE" : "FALSE");
}
void read_pmc_pm_base_address(HANDLE h, DWORD *pPmBaseAddress) {
	// PM Base Address (PWRMBASE)
	UINT32 offset1 = 0x48;
	*pPmBaseAddress = read_pci_dword(h, 0, 31, 2, offset1 / 4);
}

////////////////////////////////////////////////////////
// Hostbridge / DRAM Controller Registers B0:F0:D0

void print_pxpepbar(DWORD64 *p) {
	printf("0:0:0_PXPEPBAR - PCI Express* Egress Port Base Address (PXPEPBAR)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> PXPEPBAR: %08x\n", ((_PEXPEPBAR *)p)->PXPEPBAR << 12);
	BOOL enabled = ((_PEXPEPBAR *)p)->PXPEPBAREN;
	printf("   -> ENABLED: %s\n", enabled ? "TRUE" : "FALSE");
}
void read_hostbridge_pxpepbar(HANDLE h, DWORD64 *pPxpepbar) {
	// PCI Express* Egress Port Base Address (PXPEPBAR)
	UINT32 offset1 = 0x40;
	UINT32 offset2 = 0x44;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pPxpepbar = (high << 0x20) | low;
}

void print_mchbar(DWORD64 *p) {
	printf("0:0:0_MCHBAR - Host Memory Mapped Register Range Base (MCHBAR)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> MCHBAR: %08x\n", ((_MCHBAR *)p)->MCHBAR << 15);
	BOOL enabled = ((_MCHBAR *)p)->MCHBAREN;
	printf("   -> ENABLED: %s\n", enabled ? "TRUE" : "FALSE");
}
void read_hostbridge_mchbar(HANDLE h, DWORD64 *pMchbar) {
	// Host Memory Mapped Register Range Base (MCHBAR)
	UINT32 offset1 = 0x48;
	UINT32 offset2 = 0x4C;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pMchbar = (high << 0x20) | low;
}

void print_gmch(WORD *p) {
	printf("0:0:0_GMCH - GMCH Graphics Control Register (GGC)\n");
	printf(" => Value: %04x\n", *p);
	printf("   -> Device2 Enabled : %s\n", ((_GMCH *)p)->IVD ? "FALSE" : "TRUE");
	printf("   -> LOCKED: %s\n", ((_GMCH *)p)->GGCLCK ? "TRUE" : "FALSE");
}
void read_hostbridge_gmch(HANDLE h, WORD *pGmch) {
	// GMCH Graphics Control Register (GGC)
	UINT32 offset1 = 0x50;
	*pGmch = read_pci_word(h, 0, 0, 0, offset1 / 4);
}

void print_deven(DWORD *p) {
	printf("0:0:0_DEVEN - Device Enable (DEVEN)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> D0EN: %s\n", ((_DEVEN *)p)->D0EN ? "TRUE" : "FALSE"); 
	printf("   -> D1F2EN: %s\n", ((_DEVEN *)p)->D1F2EN ? "TRUE" : "FALSE");
	printf("   -> D1F1EN: %s\n", ((_DEVEN *)p)->D1F1EN ? "TRUE" : "FALSE");
	printf("   -> D1F0EN: %s\n", ((_DEVEN *)p)->D1F0EN ? "TRUE" : "FALSE");
	printf("   -> D2EN: %s\n", ((_DEVEN *)p)->D2EN ? "TRUE" : "FALSE");
	printf("   -> D3EN: %s\n", ((_DEVEN *)p)->D3EN ? "TRUE" : "FALSE");
	printf("   -> D4EN: %s\n", ((_DEVEN *)p)->D4EN ? "TRUE" : "FALSE");
	printf("   -> D5EN: %s\n", ((_DEVEN *)p)->D5EN ? "TRUE" : "FALSE");
	printf("   -> D7EN: %s\n", ((_DEVEN *)p)->D7EN ? "TRUE" : "FALSE");
	printf("   -> D8EN: %s\n", ((_DEVEN *)p)->D8EN ? "TRUE" : "FALSE");
}
void read_hostbridge_deven(HANDLE h, DWORD *pDeven) {
	// Device Enable (DEVEN)
	UINT32 offset1 = 0x54;
	*pDeven = read_pci_dword(h, 0, 0, 0, offset1 / 4);	
}

void print_pavpc(DWORD *p) {
	printf("0:0:0_PAVPC - Protected Audio Video Path Control (PAVPC)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> PCMBASE: %08x\n", ((_PAVPC *)p)->PCMBASE<<20);
	printf("   -> PCME: %s\n", ((_PAVPC *)p)->PCME ? "TRUE" : "FALSE");
	printf("   -> PAVPE: %s\n", ((_PAVPC *)p)->PAVPE ? "TRUE" : "FALSE");
	printf("   -> PAVPLCK: %s\n", ((_PAVPC *)p)->PAVPLCK ? "TRUE" : "FALSE");
}
void read_hostbridge_pavpc(HANDLE h, DWORD *pPavpc) {
	// Protected Audio Video Path Control (PAVPC)
	UINT32 offset1 = 0x58;
	*pPavpc = read_pci_dword(h, 0, 0, 0, offset1 / 4);
}

void print_dpr(DWORD *p) {
	printf("0:0:0_DPR - DMA Protected Range (DPR)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> TopOfDPR: %08x\n", ((_DPR *)p)->TopOfDPR << 20);
	printf("   -> DPRSIZE (in MB): %08x\n", ((_DPR *)p)->DPRSIZE);
	printf("   -> DMA Requests Blocked: %s\n", ((_DPR *)p)->EPM ? "TRUE" : "FALSE");
	printf("   -> DPR Protection Enabled: %s\n", ((_DPR *)p)->PRS ? "TRUE" : "FALSE");
	printf("   -> LOCK: %s\n", ((_DPR *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_dpr(HANDLE h, DWORD *pDpr) {
	// DMA Protected Range (DPR)
	UINT32 offset1 = 0x5C;
	*pDpr = read_pci_dword(h, 0, 0, 0, offset1 / 4);
}

void print_pciexbar(DWORD64 *p) {
	printf("0:0:0_PCIEXBAR - PCI Express Register Range Base Address (PCIEXBAR)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> PCIEXBAR: %08x\n", ((_PCIEXBAR *)p)->PCIEXBAR << 28);
	switch (((_PCIEXBAR *)p)->LENGTH) {
		case 0:
			printf("   -> LENGTH: 256MB\n");
			break;
		case 1:
			printf("   -> LENGTH: 128MB\n");
			break;
		case 2:
			printf("   -> LENGTH: 64MB\n");
			break;
		case 3:
			printf("   -> LENGTH: Reserved\n");
			break;
	}		
	printf("   -> PCIEXBAREN: %s\n", ((_PCIEXBAR *)p)->PCIEXBAREN ? "TRUE" : "FALSE");
}
void read_hostbridge_pciexbar(HANDLE h, DWORD64 *pPciexbar) {
	// PCI Express Register Range Base Address (PCIEXBAR)
	UINT32 offset1 = 0x60;
	UINT32 offset2 = 0x64;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pPciexbar = (high << 0x20) | low;
}

void print_dmibar(DWORD64 *p) {
	printf("0:0:0_DMIBAR - Root Complex Register Range Base Address (DMIBAR)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> DMIBAR: %08x\n", ((_DMIBAR *)p)->DMIBAR << 12);
	printf("   -> DMIBAREN: %s\n", ((_DMIBAR *)p)->DMIBAREN ? "TRUE" : "FALSE");
}
void read_hostbridge_dmibar(HANDLE h, DWORD64 *pDmibar) {
	// Root Complex Register Range Base Address (DMIBAR)
	UINT32 offset1 = 0x68;
	UINT32 offset2 = 0x6C;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pDmibar = (high << 0x20) | low;
}

void print_mesegbase(DWORD64 *p) {
	printf("0:0:0_MESEG_BASE - Manageability Engine Base Address Register (MESEG)\n");
	printf(" => Value: %p\n", *p);
	printf("    -> MEBASE: %08x\n", ((_MESEG_BASE *)p)->MEBASE << 20);	
}
void read_hostbridge_meseg_base(HANDLE h, DWORD64 *pMsegBase) {
	// Manageability Engine Base Address Register (MESEG)
	UINT32 offset1 = 0x70;
	UINT32 offset2 = 0x74;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pMsegBase = (high << 0x20) | low;
}

void print_meseglimit(DWORD64 *p) {
	printf("0:0:0_MESEG_LIMIT - Manageability Engine Limit Address Register (MESEG)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> MEMASK: %08x\n", ((_MESEG_LIMIT *)p)->MEMASK << 20);
	printf("   -> ME_STLEN_EN: %s\n", ((_MESEG_LIMIT *)p)->ME_STLEN_EN ? "TRUE" : "FALSE");
	printf("   -> MELCK: %s\n", ((_MESEG_LIMIT *)p)->MELCK ? "TRUE" : "FALSE");
}
void read_hostbridge_meseg_limit(HANDLE h, DWORD64 *pMsegLimit) {
	// Manageability Engine Limit Address Register (MESEG)
	UINT32 offset1 = 0x78;
	UINT32 offset2 = 0x7C;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pMsegLimit = (high << 0x20) | low;
}

void print_smramc(BYTE *p) {
	printf("0:0:0_SMRAMC - System Management RAM Control (SMRAMC)\n");
	printf(" => Value: %02x\n", *p);
	printf("   -> C_BASE_SEG: %02x\n", ((_SMRAMC *)p)->C_BASE_SEG );	
	printf("   -> G_SMRAME (Compatible SMRAM): %s\n", ((_SMRAMC *)p)->G_SMRAME ? "TRUE" : "FALSE");
	printf("   -> D_LCK: %s\n", ((_SMRAMC *)p)->D_LCK ? "TRUE" : "FALSE");
	printf("   -> D_CLS: %s\n", ((_SMRAMC *)p)->D_CLS ? "TRUE" : "FALSE");
	printf("   -> D_OPEN: %s\n", ((_SMRAMC *)p)->D_OPEN ? "TRUE" : "FALSE");
}
void read_hostbridge_smramc(HANDLE h, BYTE *pSmramc) {
	// System Management RAM Control (SMRAMC)
	UINT32 offset1 = 0x88;
	*pSmramc = read_pci_byte(h, 0, 0, 0, offset1 / 4);
}

void print_remapbase(DWORD64 *p) {
	printf("0:0:0_REMAPBASE - Remap Base Address Register (REMAPBASE)\n");
	printf(" => Value: %px\n", *p);
	printf("   -> REMAPBASE: %08x\n", ((_REMAPBASE *)p)->REMAPBASE<<20);
	printf("   -> LOCK: %s\n", ((_REMAPBASE *)p)->LOCK ? "TRUE" : "FALSE");	
}
void read_hostbridge_remap_base(HANDLE h, DWORD64 *pRemapBase) {
	// Remap Base Address Register (REMAPBASE)
	UINT32 offset1 = 0x90;
	UINT32 offset2 = 0x94;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pRemapBase = (high << 0x20) | low;
}

void print_remaplimit(DWORD64 *p) {
	printf("0:0:0_REMAPLIMIT - Remap Limit Address Register (REMAPLIMIT)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> REMAPLMT: %08x\n", ((_REMAPLIMIT *)p)->REMAPLMT<<20);
	printf("   -> LOCK: %s\n", ((_REMAPLIMIT *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_remap_limit(HANDLE h, DWORD64 *pRemapLimit) {
	// Remap Limit Address Register (REMAPLIMIT)
	UINT32 offset1 = 0x98;
	UINT32 offset2 = 0x9C;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pRemapLimit = (high << 0x20) | low;
}

void print_tom(DWORD64 *p) {
	printf("0:0:0_TOM - Top of Memory (TOM)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> TOM: %ph\n", ((_TOM *)p)->TOM << 20);
	printf("   -> LOCK: %s\n", ((_TOM *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_tom(HANDLE h, DWORD64 *pTom) {
	// Top of Memory (TOM)
	UINT32 offset1 = 0xA0;
	UINT32 offset2 = 0xA4;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pTom = (high << 0x20) | low;
}

void print_touud(DWORD64 *p) {
	printf("0:0:0_TOUUD - Top of Upper Usable DRAM (TOUUD)\n");
	printf(" => Value: %p\n", *p);
	printf("   -> TOUUD: %ph\n", ((_TOUUD *)p)->TOUUD << 20);
	printf("   -> LOCK: %s\n", ((_TOUUD *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_touud(HANDLE h, DWORD64 *pTouud) {
	// Top of Upper Usable DRAM (TOUUD)
	UINT32 offset1 = 0xA8;
	UINT32 offset2 = 0xAC;
	DWORD64 low = read_pci_dword(h, 0, 0, 0, offset1 / 4);
	DWORD64 high = read_pci_dword(h, 0, 0, 0, offset2 / 4);
	*pTouud = (high << 0x20) | low;
}

void print_bdsm(DWORD *p) {
	printf("0:0:0_BDSM - Base Data of Stolen Memory (BDSM)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> BDSM: %08xh\n", ((_BDSM *)p)->BDSM << 20);
	printf("   -> LOCK: %s\n", ((_BDSM *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_bdsm(HANDLE h, DWORD *pBdsm) {
	// Base Data of Stolen Memory (BDSM)
	UINT32 offset1 = 0xB0;
	*pBdsm = read_pci_dword(h, 0, 0, 0, offset1 / 4);
}

void print_bgsm(DWORD *p) {
	printf("0:0:0_BGSM - Base of GTT Stolen Memory (BGSM)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> BGSM: %08xh\n", ((_BGSM *)p)->BGSM << 20);
	printf("   -> LOCK: %s\n", ((_BGSM *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_bgsm(HANDLE h, DWORD *pBgsm) {
	// Base of GTT Stolen Memory (BGSM)
	UINT32 offset1 = 0xB4;
	*pBgsm = read_pci_dword(h, 0, 0, 0, offset1 / 4);
}

void print_tsegmb(DWORD *p) {
	printf("0:0:0_TSEGMB - TSEG Memory Base (TSEGMB)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> TSEGMB: %08xh\n", ((_TSEGMB *)p)->TSEGMB << 20);
	printf("   -> LOCK: %s\n", ((_TSEGMB *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_tseg(HANDLE h, DWORD *pTseg) {
	// TSEG Memory Base (TSEGMB)
	UINT32 offset1 = 0xB8;
	*pTseg = read_pci_dword(h, 0, 0, 0, offset1 / 4);
}

void print_tolud(DWORD *p) {
	printf("0:0:0_TOLUD - Top of Low Usable DRAM (TOLUD)\n");
	printf(" => Value: %08x\n", *p);
	printf("   -> TOLUD: %08xh\n", ((_TOLUD *)p)->TOLUD << 20);
	printf("   -> LOCK: %s\n", ((_TOLUD *)p)->LOCK ? "TRUE" : "FALSE");
}
void read_hostbridge_tolud(HANDLE h, DWORD *pTolud) {
	// Top of Low Usable DRAM (TOLUD)
	UINT32 offset1 = 0xBC;
	*pTolud = read_pci_dword(h, 0, 0, 0, offset1 / 4);
}

//////////////////////////////////////////////////////////////

void get_chipset_id(
	HANDLE h,
	WORD *platformVID,
	WORD *platformDID,
	WORD *PCHVID,
	WORD *PCHDID)
{
	DWORD platform = read_pci_dword(h, 0, 0, 0, 0);
	*platformVID = platform & 0xFFFF;
	*platformDID = platform >> 0x10;
	DWORD pch = read_pci_dword(h, 0, 0x1f, 0, 0);
	*PCHVID = pch & 0xFFFF;
	*PCHDID = pch >> 0x10;
}

//////////////////////////////////////////////////////////////

void read_pci_header(HANDLE h, UINT8 bus, UINT8 device, UINT8 function) {

	PPCI_CONFIG_HEADER pciHeader = (PPCI_CONFIG_HEADER)HeapAlloc(
		GetProcessHeap(), HEAP_ZERO_MEMORY, 256);

	READ_PCI_CONFIGURATION_SPACE_CALL pci_config_call = { 0 };
	pci_config_call.bus = bus;
	pci_config_call.device = device;
	pci_config_call.function = function;

	DWORD bytesReturned = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_PCI_HEADER,
		&pci_config_call, sizeof(READ_PCI_CONFIGURATION_SPACE_CALL),
		pciHeader, 256, &bytesReturned, NULL);
	printf("Status: %08x - Error: %08x\n", status, GetLastError());

	printf("DeviceId: %04x\n", pciHeader->DeviceId);
	printf("VendorId: %04x\n", pciHeader->VendorId);
	printf("Status: %04x\n", pciHeader->Status);
	printf("Command: %04x\n", pciHeader->Command);
	printf("ClassCode: %06x\n", pciHeader->ClassCode);
	printf("BAR0: %08x\n", pciHeader->BAR0.BaseAddress);
	printf("BAR1: %08x\n", pciHeader->BAR1.BaseAddress);
	printf("BAR2: %08x\n", pciHeader->BAR2.BaseAddress);
	printf("BAR3: %08x\n", pciHeader->BAR3.BaseAddress);
	printf("BAR4: %08x\n", pciHeader->BAR4.BaseAddress);
	printf("BAR5: %08x\n", pciHeader->BAR5.BaseAddress);
	print_memory(0x0, (char *)pciHeader, 256);

	HeapFree(GetProcessHeap(), 0, pciHeader);
}

BYTE read_pci_byte(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset) {
	READ_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	DWORD bytesReturned = 0;
	BYTE aux;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_PCI_BYTE,
		&pci_call, sizeof(READ_PCI_DATA_CALL),
		&aux, sizeof(BYTE), &bytesReturned, NULL);
	if (NT_SUCCESS(status)) {
		printf("-> One byte read from %02x:%02x:%02x offset %08xh: %02xh\n",
			bus, device, function, offset << 2, aux);
	}
	return aux;
}

WORD read_pci_word(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset) {
	READ_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	DWORD bytesReturned = 0;
	WORD aux;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_PCI_WORD,
		&pci_call, sizeof(READ_PCI_DATA_CALL),
		&aux, sizeof(WORD), &bytesReturned, NULL);
	if (NT_SUCCESS(status)) {
		printf("-> One word read from %02x:%02x:%02x offset %08xh: %04xh\n",
			bus, device, function, offset << 2, aux);
	}
	return aux;
}

DWORD read_pci_dword(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset) {
	READ_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	DWORD bytesReturned = 0;
	DWORD aux;
	NTSTATUS status = DeviceIoControl(h, IOCTL_READ_PCI_DWORD,
		&pci_call, sizeof(READ_PCI_DATA_CALL),
		&aux, sizeof(DWORD), &bytesReturned, NULL);
	if (NT_SUCCESS(status)) {
		printf("-> One dword read from %02x:%02x:%02x offset %08xh: %08xh\n",
			bus, device, function, offset << 2, aux);
	}
	return aux;
}

void write_pci_byte(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset, UINT value) {
	WRITE_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	pci_call.value = value;
	DWORD bytesReturned = 0;

	NTSTATUS status = DeviceIoControl(h, IOCTL_WRITE_PCI_BYTE,
		&pci_call, sizeof(WRITE_PCI_DATA_CALL),
		NULL, 0, &bytesReturned, NULL);
	if (NT_SUCCESS(status)) {
		printf("-> One byte written into %02x:%02x:%02x offset %08xh: %02xh\n",
			bus, device, function, offset << 2, value);
	}
}

void write_pci_word(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset, UINT value) {
	WRITE_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	pci_call.value = value;
	DWORD bytesReturned = 0;

	NTSTATUS status = DeviceIoControl(h, IOCTL_WRITE_PCI_WORD,
		&pci_call, sizeof(WRITE_PCI_DATA_CALL),
		NULL, 0, &bytesReturned, NULL);
	if (NT_SUCCESS(status)) {
		printf("-> One word written into %02x:%02x:%02x offset %08xh: %04xh\n",
			bus, device, function, offset << 2, value);
	}
}

void write_pci_dword(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset, UINT value) {
	WRITE_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	pci_call.value = value;
	DWORD bytesReturned = 0;

	NTSTATUS status = DeviceIoControl(h, IOCTL_WRITE_PCI_DWORD,
		&pci_call, sizeof(WRITE_PCI_DATA_CALL),
		NULL, 0, &bytesReturned, NULL);
	if (NT_SUCCESS(status)) {
		printf("-> One dword written into %02x:%02x:%02x offset %08xh: %08xh\n",
			bus, device, function, offset << 2, value);
	}
}

void read_pci_bar_info(HANDLE h, UINT8 bus, UINT8 device, UINT8 function, UINT offset) {
	// Assumes a BAR at offset and retrieves it's size and settings
	DWORD bar = read_pci_dword(h, bus, device, function, offset);
	PPCI_BAR p = (PPCI_BAR)&bar;
	printf("-> BAR at %08xh: \n", offset);
	if (p->IOMapped) {
		printf("---> Type: IO-Mapped\n");
	}
	else {
		printf("---> Type: Memory-Mapped\n");
	}
	if (p->Prefetchable) {
		printf("---> Prefetchable: TRUE\n");
	}
	else {
		printf("---> Prefetchable: FALSE\n");
	}
	UINT64 bar_size = 0;
	READ_PCI_DATA_CALL pci_call = { 0 };
	pci_call.bus = bus;
	pci_call.device = device;
	pci_call.function = function;
	pci_call.offset = offset;
	DWORD bytesReturned = 0;
	NTSTATUS status = DeviceIoControl(h, IOCTL_GET_PCI_BAR_SIZE,
		&pci_call, sizeof(READ_PCI_DATA_CALL),
		&bar_size, sizeof(PVOID), &bytesReturned, NULL);
	bar_size = bar_size ^ 0xFFFFFFFF;
	printf("---> BaseAddress: %ph - Size: %ph\n", p->BaseAddress << 4, bar_size);

}

void parse_bus_device_function(char *line, UINT *bus, UINT *device, UINT *function) {
	char **subargs = parse_arguments(line, ':');
	int subargc = (int)subargs[0];
	subargc--;
	if (subargc == 3) {
		*bus = strtoul(subargs[1], NULL, 10);
		*device = strtoul(subargs[2], NULL, 10);
		*function = strtoul(subargs[3], NULL, 10);
	}
	free(subargs);
}

void parse_handle_pci_operation(HANDLE h, int argc, char **argv) {
	// pci r 0:2:0 -> reads the configuration space
	// pci rb 0:2:0 1 -> reads a byte from offset 
	// pci rw 0:2:0 1 -> reads a word from offset 1*4
	// pci rd 0:2:0 1 -> reads a dword from offset 1*4
	// pci wb 0:2:0 1 0x90 -> writes a byte to offset 1*4
	// pci ww 0:2:0 1 0x9090 -> writes a word to offset 1*4
	// pci wd 0:2:0 1 0x90909090 -> writes a dword to offset 1*4
	// pci r bar 0:2:0 0x10 -> read BAR info at offset 0x10
	UINT bus, device, function = 0;
	UINT offset = 0;
	UINT value = 0;
	if (!strcmp(argv[1], "r")) {
		if (argc == 3) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			read_pci_header(h, bus, device, function);
		}
		else if (argc == 5 && !strcmp(argv[2], "bar")) {
			parse_bus_device_function(argv[3], &bus, &device, &function);
			offset = strtoul(argv[4], NULL, 16);
			read_pci_bar_info(h, bus, device, function, offset >> 2);
		}
	}
	else if (!strcmp(argv[1], "rb")) {
		if (argc == 4) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			offset = strtoul(argv[3], NULL, 16);
			read_pci_byte(h, bus, device, function, offset >> 2);
		}
	}
	else if (!strcmp(argv[1], "rw")) {
		if (argc == 4) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			offset = strtoul(argv[3], NULL, 16);
			read_pci_word(h, bus, device, function, offset >> 2);
		}
	}
	else if (!strcmp(argv[1], "rd")) {
		if (argc == 4) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			offset = strtoul(argv[3], NULL, 16);
			read_pci_dword(h, bus, device, function, offset >> 2);
		}
	}
	else if (!strcmp(argv[1], "wb")) {
		if (argc == 5) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			offset = strtoul(argv[3], NULL, 16);
			value = strtoul(argv[4], NULL, 16);
			write_pci_byte(h, bus, device, function, offset >> 2, value);
		}
	}
	else if (!strcmp(argv[1], "ww")) {
		if (argc == 5) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			offset = strtoul(argv[3], NULL, 16);
			value = strtoul(argv[4], NULL, 16);
			write_pci_word(h, bus, device, function, offset >> 2, value);
		}
	}
	else if (!strcmp(argv[1], "wd")) {
		if (argc == 5) {
			parse_bus_device_function(argv[2], &bus, &device, &function);
			offset = strtoul(argv[3], NULL, 16);
			value = strtoul(argv[4], NULL, 16);
			write_pci_dword(h, bus, device, function, offset >> 2, value);
		}
	}
}