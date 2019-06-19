	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	lui		$t2, %hi(0x70605040)
	addi		$t2, $t2, %lo(0x70605040)

	# Zero offset, base word aligned

	lui		$t0, %hi(mem01+8)
	addi		$t0, $t0, %lo(mem01+8)
	sh		$t2, 0($t0)
	lui		$t3, %hi(mem01)
	addi		$t3, $t3, %lo(mem01)
	lw		$t1, 8($t3)
	TEST_EXPECT	$t1, 0x50403a3b

	# Positive offset, base word aligned

	lui		$t0, %hi(mem02+8)
	addi		$t0, $t0, %lo(mem02+8)
	sh		$t2, 2($t0)
	lui		$t3, %hi(mem02)
	addi		$t3, $t3, %lo(mem02)
	lw		$t1, 8($t3)
	TEST_EXPECT	$t1, 0x38395040

	# Negative offset, base word aligned

	lui		$t0, %hi(mem03+8)
	addi		$t0, $t0, %lo(mem03+8)
	sh		$t2, -2($t0)
	lui		$t3, %hi(mem03)
	addi		$t3, $t3, %lo(mem03)
	lw		$t1, 4($t3)
	TEST_EXPECT	$t1, 0x34355040

	# Zero offset, base not word aligned

	lui		$t0, %hi(mem04+6)
	addi		$t0, $t0, %lo(mem04+6)
	sh		$t2, 0($t0)
	lui		$t3, %hi(mem04)
	addi		$t3, $t3, %lo(mem04)
	lw		$t1, 4($t3)
	TEST_EXPECT	$t1, 0x34355040

	# Positive offset, base not word aligned

	lui		$t0, %hi(mem05+6)
	addi		$t0, $t0, %lo(mem05+6)
	sh		$t2, 4($t0)
	lui		$t3, %hi(mem05)
	addi		$t3, $t3, %lo(mem05)
	lw		$t1, 8($t3)
	TEST_EXPECT	$t1, 0x38395040

	# Negative offset, base not word aligned

	lui		$t0, %hi(mem06+6)
	addi		$t0, $t0, %lo(mem06+6)
	sh		$t2, -4($t0)
	lui		$t3, %hi(mem06)
	addi		$t3, $t3, %lo(mem06)
	lw		$t1, 0($t3)
	TEST_EXPECT	$t1, 0x30315040


	TEST_END

	.data
	.align	2
	
mem01:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
mem02:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
mem03:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
mem04:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
mem05:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
mem06:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
