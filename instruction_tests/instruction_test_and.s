	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test zero value
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	and		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0x00000000

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	and		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0x00000000

	lui		$t1, %hi(0x5A5A5A5A)
	addi		$t1, $t1, %lo(0x5A5A5A5A)
	and		$t2, $zero, $t1
	TEST_EXPECT	$t2, 0x00000000

	lui		$t1, %hi(0xA5A5A5A5)
	addi		$t1, $t1, %lo(0xA5A5A5A5)
	and		$t2, $zero, $t1
	TEST_EXPECT	$t2, 0x00000000

	# Test non-zero values
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	and		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x0A0A5050

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	and		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x0505A0A0

	# ################################################################

	# Test with $zero as destination
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	and		$zero, $t0, $t1
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
