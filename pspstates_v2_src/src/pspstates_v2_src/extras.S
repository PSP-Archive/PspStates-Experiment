	.set noreorder

# loc_00000D40
.global HijackPowerModuleForSaveState
.ent	HijackPowerModuleForSaveState
HijackPowerModuleForSaveState:
	move $s0, $a0
	lui $v0, 0x8A00
	sw $s0, 28($v0)
	sw $ra, 32($v0)
	lui $v1, %hi(power_jump_addr)
	addiu $v1, $v1, %lo(power_jump_addr)
	lw $v1, 0($v1)
	sw $v1, 36($v0)
	move $s1, $ra
	jal SaveProcessing
	nop
	move $ra, $s1
	addiu $sp, $sp, -16
	sw $ra, 4($sp)
	move $a0, $s0
	lui $v0, %hi(power_jump_addr)
	addiu $v0, $v0, %lo(power_jump_addr)
	lw $v0, 0($v0)
	jr $v0
	nop
.end HijackPowerModuleForSaveState

# loc_00000D90
.global power_jump_addr
.ent	power_jump_addr
power_jump_addr:
	.word 0xDADADADA
.end power_jump_addr

# 0x00000D9C
# v1‚ÌŽž‚ÌŽcŠ[‚ÅŽg‚í‚ê‚Ä‚¢‚È‚¢

.global sceCtrlReadBufferPositiveHijackFunc
.ent	sceCtrlReadBufferPositiveHijackFunc
sceCtrlReadBufferPositiveHijackFunc:
	addiu $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	move $s0, $a0
	lui $v0, %hi(ctrl_jump_addr)
	addiu $v0, $v0, %lo(ctrl_jump_addr)
	lw $v0, 0($v0)
	lui $ra, %hi(CtrlFuncLauncher)
	addiu $ra, $ra, %lo(CtrlFuncLauncher)
	addiu $sp, $sp, -16
	sw $ra, 0($sp)
	jr $v0
	nop
.end sceCtrlReadBufferPositiveHijackFunc

# loc_00000DD0
# v1‚ÌŽž‚ÌŽcŠ[‚ÅŽg‚í‚ê‚Ä‚¢‚È‚¢

.global CtrlFuncLauncher
.ent	CtrlFuncLauncher
CtrlFuncLauncher:
	move $a1, $v0
	jal sceCtrlReadBufferPositivePatched
	move $a0, $s0
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	jr $ra
	addiu $sp, $sp, 16
.end CtrlFuncLauncher

# loc_00000DEC
# v1‚ÌŽž‚ÌŽcŠ[‚ÅŽg‚í‚ê‚Ä‚¢‚È‚¢

.global ctrl_jump_addr
.ent	ctrl_jump_addr
ctrl_jump_addr:
	.word 0x33333333
	mfic $v0, $0
	jr $ra
	nop
	nop
	nop
	nop
	nop
	nop
	nop
.end ctrl_jump_addr

