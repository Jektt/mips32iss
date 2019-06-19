	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test zero value
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	or		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0x5A5A5A5A

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	or		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0xA5A5A5A5

	lui		$t1, %hi(0x5A5A5A5A)
	addi		$t1, $t1, %lo(0x5A5A5A5A)
	or		$t2, $zero, $t1
	TEST_EXPECT	$t2, 0x5A5A5A5A

	lui		$t1, %hi(0xA5A5A5A5)
	addi		$t1, $t1, %lo(0xA5A5A5A5)
	or		$t2, $zero, $t1
	TEST_EXPECT	$t2, 0xA5A5A5A5

	# Test non-zero values
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	or		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x5F5FFAFA

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	or		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0xAFAFF5F5

	# ################################################################

	# Test with $zero as destination
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	or		$zero, $t0, $t1
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
