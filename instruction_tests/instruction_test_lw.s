	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Load positive value, zero offset, base word aligned

	lui		$t0, %hi(pos+8)
	addi		$t0, $t0, %lo(pos+8)
	lw		$t1, 0($t0)
	TEST_EXPECT	$t1, 0x38393a3b

	# Load positive value, positive offset, base word aligned

	lui		$t0, %hi(pos+8)
	addi		$t0, $t0, %lo(pos+8)
	lw		$t1, 4($t0)
	TEST_EXPECT	$t1, 0x3c3d3e3f

	# Load positive value, negative offset, base word aligned

	lui		$t0, %hi(pos+8)
	addi		$t0, $t0, %lo(pos+8)
	lw		$t1, -4($t0)
	TEST_EXPECT	$t1, 0x34353637

	# Load positive value, positive offset, base not word aligned

	lui		$t0, %hi(pos+5)
	addi		$t0, $t0, %lo(pos+5)
	lw		$t1, 3($t0)
	TEST_EXPECT	$t1, 0x38393a3b

	# Load positive value, negative offset, base not word aligned

	lui		$t0, %hi(pos+5)
	addi		$t0, $t0, %lo(pos+5)
	lw		$t1, -1($t0)
	TEST_EXPECT	$t1, 0x34353637

	# ################################################################

	# Load negative value, zero offset, base word aligned

	lui		$t0, %hi(neg+8)
	addi		$t0, $t0, %lo(neg+8)
	lw		$t1, 0($t0)
	TEST_EXPECT	$t1, 0xf8f9fafb

	# Load negative value, positive offset, base word aligned

	lui		$t0, %hi(neg+8)
	addi		$t0, $t0, %lo(neg+8)
	lw		$t1, 4($t0)
	TEST_EXPECT	$t1, 0xfcfdfeff

	# Load negative value, negative offset, base word aligned

	lui		$t0, %hi(neg+8)
	addi		$t0, $t0, %lo(neg+8)
	lw		$t1, -4($t0)
	TEST_EXPECT	$t1, 0xf4f5f6f7

	# Load negative value, positive offset, base not word aligned

	lui		$t0, %hi(neg+5)
	addi		$t0, $t0, %lo(neg+5)
	lw		$t1, 3($t0)
	TEST_EXPECT	$t1, 0xf8f9fafb

	# Load negative value, negative offset, base not word aligned

	lui		$t0, %hi(neg+5)
	addi		$t0, $t0, %lo(neg+5)
	lw		$t1, -1($t0)
	TEST_EXPECT	$t1, 0xf4f5f6f7


	TEST_END

	.data
	.align	2
	
pos:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
neg:	.byte	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7
	.byte	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
	
	
