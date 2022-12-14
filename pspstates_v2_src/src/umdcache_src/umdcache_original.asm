
; ==== Section .text - Address 0x00000000 Size 0x00000074 Flags 0x0006

; ======================================================
; Subroutine module_start - Address 0x00000000 
; Exported in syslib
module_start:		; Refs: 0x00000128 
	0x00000000: 0x27BDFFF8 '...'' - addiu      $sp, $sp, -8
	0x00000004: 0xAFBF0000 '....' - sw         $ra, 0($sp)
	0x00000008: 0x0C000021 '!...' - jal        sceKernelGetModel
	0x0000000C: 0x00000000 '....' - nop        
	0x00000010: 0x24030001 '...$' - li         $v1, 1
	0x00000014: 0x14430014 '..C.' - bne        $v0, $v1, loc_00000068
	0x00000018: 0x8FBF0000 '....' - lw         $ra, 0($sp)
	0x0000001C: 0x0C00001F '....' - jal        sceKernelApplicationType
	0x00000020: 0x00000000 '....' - nop        
	0x00000024: 0x24030200 '...$' - li         $v1, 512
	0x00000028: 0x1443000F '..C.' - bne        $v0, $v1, loc_00000068
	0x0000002C: 0x8FBF0000 '....' - lw         $ra, 0($sp)
	0x00000030: 0x0C00001D '....' - jal        sceKernelBootFrom
	0x00000034: 0x00000000 '....' - nop        
	0x00000038: 0x24030040 '@..$' - li         $v1, 64
	0x0000003C: 0x1443000A '..C.' - bne        $v0, $v1, loc_00000068
	0x00000040: 0x8FBF0000 '....' - lw         $ra, 0($sp)
	0x00000044: 0x3C02BC00 '...<' - lui        $v0, 0xBC00
	0x00000048: 0x34440080 '..D4' - ori        $a0, $v0, 0x80
	0x0000004C: 0x2403FFFF '...$' - li         $v1, -1
	0x00000050: 0x34420040 '@.B4' - ori        $v0, $v0, 0x40
	0x00000054: 0xAC430000 '..C.' - sw         $v1, 0($v0)

loc_00000058:		; Refs: 0x0000005C 
	0x00000058: 0x24420004 '..B$' - addiu      $v0, $v0, 4
	0x0000005C: 0x5444FFFE '..DT' - bnel       $v0, $a0, loc_00000058
	0x00000060: 0xAC430000 '..C.' - sw         $v1, 0($v0)
	0x00000064: 0x8FBF0000 '....' - lw         $ra, 0($sp)

loc_00000068:		; Refs: 0x00000014 0x00000028 0x0000003C 
	0x00000068: 0x24020001 '...$' - li         $v0, 1
	0x0000006C: 0x03E00008 '....' - jr         $ra
	0x00000070: 0x27BD0008 '...'' - addiu      $sp, $sp, 8

; ==== Section .sceStub.text - Address 0x00000074 Size 0x00000018 Flags 0x0006

; ======================================================
; Subroutine sceKernelBootFrom - Address 0x00000074 
; Imported from InitForKernel
sceKernelBootFrom:		; Refs: 0x000000B8 0x00000030 
	0x00000074: 0x03E00008 '....' - jr         $ra
	0x00000078: 0x00000000 '....' - nop        

; ======================================================
; Subroutine sceKernelApplicationType - Address 0x0000007C 
; Imported from InitForKernel
sceKernelApplicationType:		; Refs: 0x0000001C 
	0x0000007C: 0x03E00008 '....' - jr         $ra
	0x00000080: 0x00000000 '....' - nop        

; ======================================================
; Subroutine sceKernelGetModel - Address 0x00000084 
; Imported from SysMemForKernel
sceKernelGetModel:		; Refs: 0x000000CC 0x00000008 
	0x00000084: 0x03E00008 '....' - jr         $ra
	0x00000088: 0x00000000 '....' - nop        

; ==== Section .lib.ent.top - Address 0x0000008C Size 0x00000004 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x0000008C - 00 00 00 00 | -- -- -- -- | -- -- -- -- | -- -- -- -- - ................

; ==== Section .lib.ent - Address 0x00000090 Size 0x00000010 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x00000090 - 00 00 00 00 | 00 00 00 80 | 04 01 01 00 | 20 01 00 00 - ............ ...

; ==== Section .lib.ent.btm - Address 0x000000A0 Size 0x00000004 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x000000A0 - 00 00 00 00 | -- -- -- -- | -- -- -- -- | -- -- -- -- - ................

; ==== Section .lib.stub.top - Address 0x000000A4 Size 0x00000004 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x000000A4 - 00 00 00 00 | -- -- -- -- | -- -- -- -- | -- -- -- -- - ................

; ==== Section .lib.stub - Address 0x000000A8 Size 0x00000028 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x000000A8 - 34 01 00 00 | 11 00 09 00 | 05 00 02 00 | 58 01 00 00 - 4...........X...
0x000000B8 - 74 00 00 00 | 48 01 00 00 | 11 00 01 00 | 05 00 01 00 - t...H...........
0x000000C8 - 60 01 00 00 | 84 00 00 00 | -- -- -- -- | -- -- -- -- - `...............

; ==== Section .lib.stub.btm - Address 0x000000D0 Size 0x00000004 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x000000D0 - 00 00 00 00 | -- -- -- -- | -- -- -- -- | -- -- -- -- - ................

; ==== Section .rodata.sceModuleInfo - Address 0x000000E0 Size 0x00000040 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x000000E0 - 06 10 01 01 | 70 73 70 55 | 6D 64 43 61 | 63 68 65 5F - ....pspUmdCache_
0x000000F0 - 44 75 6D 6D | 79 00 00 00 | 00 00 00 00 | 00 00 00 00 - Dummy...........
0x00000100 - 60 82 00 00 | 90 00 00 00 | A0 00 00 00 | A8 00 00 00 - `...............
0x00000110 - D0 00 00 00 | 00 00 00 00 | 00 00 00 00 | 00 00 00 00 - ................

; Strings
0x000000E4: "pspUmdCache_Dummy"

; ==== Section .rodata.sceResident - Address 0x00000120 Size 0x00000038 Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x00000120 - DB AC 32 D6 | A7 73 1D F0 | 00 00 00 00 | E0 00 00 00 - ..2..s..........
0x00000130 - 00 00 00 00 | 49 6E 69 74 | 46 6F 72 4B | 65 72 6E 65 - ....InitForKerne
0x00000140 - 6C 00 00 00 | 00 00 00 00 | 53 79 73 4D | 65 6D 46 6F - l.......SysMemFo
0x00000150 - 72 4B 65 72 | 6E 65 6C 00 | -- -- -- -- | -- -- -- -- - rKernel.........

; Strings
0x00000134: "InitForKernel"
0x00000148: "SysMemForKernel"

; ==== Section .rodata.sceNid - Address 0x00000158 Size 0x0000000C Flags 0x0002
           - 00 01 02 03 | 04 05 06 07 | 08 09 0A 0B | 0C 0D 0E 0F - 0123456789ABCDEF
-------------------------------------------------------------------------------------
0x00000158 - 88 23 93 27 | BC B5 33 72 | 5D 99 73 63 | -- -- -- -- - .#.'..3r].sc....
