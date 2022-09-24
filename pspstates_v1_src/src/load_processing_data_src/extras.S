	.set noreorder

# sub_040E004C
.global sub_040E004C
.ent	sub_040E004C
sub_040E004C:
	.word 0x40088000
	li $t1, 2048
	ext $t0, $t0, 6, 3
	sllv $t1, $t1, $t0
	move $t0, $zero

$jump_loc_040E0060:
	cache 0x10, 0($t0)
	.word 0x400AE000
	.word 0x400BE800
	ext $t4, $t2, 20, 1
	beqz $t4, $jump_loc_040E0084
	ext $t4, $t3, 20, 1
	sll $t2, $t2, 13
	or $t2, $t2, $t0
	cache 0x1A, 0($t2)

$jump_loc_040E0084:
	beqz $t4, $jump_loc_040E0094
	sll $t3, $t3, 13
	or $t3, $t3, $t0
	cache 0x1A, 0($t3)

$jump_loc_040E0094:
	addiu $t0, $t0, 64
	bne $t0, $t1, $jump_loc_040E0060
	nop
	jr $ra
	sync
.end sub_040E004C

# sub_040E00A8
.global sub_040E00A8
.ent	sub_040E00A8
sub_040E00A8:
	.word 0x40088000
	li $t1, 4096
	ext $t0, $t0, 9, 3
	sllv $t1, $t1, $t0
	.word 0x4080E000
	.word 0x4080E800
	move $t0, $zero

$jump_loc_040E00C4:
	cache 0x1, 0($t0)
	cache 0x3, 0($t0)
	addiu $t0, $t0, 64
	bne $t0, $t1, $jump_loc_040E00C4
	nop
	jr $ra
	nop
.end sub_040E00A8

