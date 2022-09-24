// LoadProcessing

// header
#include <pspkernel.h>

// prototype
void sub_040E004C(void);
void sub_040E00A8(void);
int fastlz_decompress(const void *input, int length, void *output, int maxout);

// sub_040E00E0
void DecompressMemory(void)
{
	u32 *dest, src, i;

	dest = (u32 *)0x8A000028;
	src = *(u32 *)0x8A00001C;

	// restore
	for(i = 0; i < 88; i += 4)
		*(u32 *)(src + i) = *dest++;

	// decompress
	fastlz_decompress((void *)(0x8A000000 + _lw(0x8A00000C)), _lw(0x8A000010), (void *)0x88000000, 0x2000000);
	fastlz_decompress((void *)(0x8A000000 + _lw(0x8A000014)), _lw(0x8A000018), (void *)0x8BC00000, 0x400000);

	return;
}

// _start
void MainBinEntry(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2) __attribute__ ((section (".text.start")));
void MainBinEntry(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2)
{
	asm("move $s2, $sp");
	asm("lui $v0, 0x8A00");
	asm("li $v1, -1");
	asm("sw $v1, 8($v0)");
	asm("lui $sp, 0x40D");
	asm("jal DecompressMemory");
	asm("jal sub_040E004C");
	asm("jal sub_040E00A8");
	asm("move $sp, $s2");
	asm("lui $v0, 0x8A00");
	asm("lw $a0, 28($v0)");
	asm("lw $ra, 32($v0)");
	asm("lw $v1, 36($v0)");
	asm("addiu $sp, $sp, -16");
	asm("sw $ra, 4($sp)");
	asm("jr $v1");
}

