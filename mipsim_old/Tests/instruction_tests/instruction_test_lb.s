	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Load positive value, zero offset, base word aligned

	lui		$t0, %hi(pos+8)
	addi		$t0, $t0, %lo(pos+8)
	lb		$t1, 0($t0)
	TEST_EXPECT	$t1, 0x00000038

	# Load positive value, positive offset, base word aligned

	lui		$t0, %hi(pos+8)
	addi		$t0, $t0, %lo(pos+8)
	lb		$t1, 2($t0)
	TEST_EXPECT	$t1, 0x0000003a

	# Load positive value, negative offset, base word aligned

	lui		$t0, %hi(pos+8)
	addi		$t0, $t0, %lo(pos+8)
	lb		$t1, -2($t0)
	TEST_EXPECT	$t1, 0x00000036

	# Load positive value, zero offset, base not word aligned

	lui		$t0, %hi(pos+7)
	addi		$t0, $t0, %lo(pos+7)
	lb		$t1, 0($t0)
	TEST_EXPECT	$t1, 0x00000037

	# Load positive value, positive offset, base not word aligned

	lui		$t0, %hi(pos+7)
	addi		$t0, $t0, %lo(pos+7)
	lb		$t1, 2($t0)
	TEST_EXPECT	$t1, 0x00000039

	# Load positive value, negative offset, base not word aligned

	lui		$t0, %hi(pos+7)
	addi		$t0, $t0, %lo(pos+7)
	lb		$t1, -2($t0)
	TEST_EXPECT	$t1, 0x00000035

	# ################################################################

	# Load negative value, zero offset, base word aligned

	lui		$t0, %hi(neg+8)
	addi		$t0, $t0, %lo(neg+8)
	lb		$t1, 0($t0)
	TEST_EXPECT	$t1, 0xfffffff8

	# Load negative value, positive offset, base word aligned

	lui		$t0, %hi(neg+8)
	addi		$t0, $t0, %lo(neg+8)
	lb		$t1, 2($t0)
	TEST_EXPECT	$t1, 0xfffffffa

	# Load negative value, negative offset, base word aligned

	lui		$t0, %hi(neg+8)
	addi		$t0, $t0, %lo(neg+8)
	lb		$t1, -2($t0)
	TEST_EXPECT	$t1, 0xfffffff6

	# Load negative value, zero offset, base not word aligned

	lui		$t0, %hi(neg+7)
	addi		$t0, $t0, %lo(neg+7)
	lb		$t1, 0($t0)
	TEST_EXPECT	$t1, 0xfffffff7

	# Load negative value, positive offset, base not word aligned

	lui		$t0, %hi(neg+7)
	addi		$t0, $t0, %lo(neg+7)
	lb		$t1, 2($t0)
	TEST_EXPECT	$t1, 0xfffffff9

	# Load negative value, negative offset, base not word aligned

	lui		$t0, %hi(neg+7)
	addi		$t0, $t0, %lo(neg+7)
	lb		$t1, -2($t0)
	TEST_EXPECT	$t1, 0xfffffff5


	TEST_END

	.data
	.align	2
	
pos:	.byte	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
	.byte	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	
neg:	.byte	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7
	.byte	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
	
	
