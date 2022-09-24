// SaveProcessing

// header
#include <pspkernel.h>

// prototype
int fastlz_compress_level(int level, const void *input, int length, void *output);

// sub_040E001C
void CompressMemory(void)
{
	u32 *dest, src;
	int i, size, raw_size;

	dest = (u32 *)0x8A000028;
	src = *(u32 *)0x8A00001C;

	// backup
	for(i = 0; i < 88; i += 4)
		*dest++ = *(u32 *)(src + i);

	// set
	_sw(0xDADADADA, 0x8A000000);
	_sw(0x33333333, 0x8A000004);
	_sw(0x00000003, 0x8A000008);
	_sw(0x00000100, 0x8A00000C);

	// compress
	raw_size = fastlz_compress_level(1, (void *)0x88000000, 0x2000000, (void *)0x8A000100);

	// get
	size = (raw_size & -0x10) + 272;

	// set
	_sw(size, 0x8A000010);
	_sw(raw_size, 0x8A000014);

	// compress
	raw_size = fastlz_compress_level(1, (void *)0x8BC00000, 0x400000, (void *)(0x8A000000 + size));

	// set
	_sw(raw_size, 0x8A000018);
	return;
}

// _start
void MainBinEntry(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2) __attribute__ ((section (".text.start")));
void MainBinEntry(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2)
{
	asm("move $s2, $sp");
	asm("move $s3, $ra");
	asm("lui $sp, 0x40D");
	asm("jal CompressMemory");
	asm("move $ra, $s3");
	asm("move $sp, $s2");
}

