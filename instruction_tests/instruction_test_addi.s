	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test positive/zero value
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	addi		$t1, $t0, 0
	TEST_EXPECT	$t1, 0x5A5A5A5A

	# Test positive/positive value, no overflow
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	addi		$t1, $t0, 16
	TEST_EXPECT	$t1, 0x5A5A5A6A

	# Test positive/negative value
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	addi		$t1, $t0, -16
	TEST_EXPECT	$t1, 0x5A5A5A4A

	# Test positive/positive value, overflow
	lui		$t0, %hi(0x7FFFFFFF)
	addi		$t0, $t0, %lo(0x7FFFFFFF)
	addi		$t1, $t0, 16
	TEST_EXPECT	$t1, 0x8000000F

	# ################################################################

	# Test negative/zero value
	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	addi		$t1, $t0, 0
	TEST_EXPECT	$t1, 0xA5A5A5A5

	# Test negative/positive value
	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	addi		$t1, $t0, 16
	TEST_EXPECT	$t1, 0xA5A5A5B5
	
	# Test negative/negative value, no overflow
	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	addi		$t1, $t0, -16
	TEST_EXPECT	$t1, 0xA5A5A595

	# Test negative/negative value, overflow
	lui		$t0, %hi(0x8000000F)
	addi		$t0, $t0, %lo(0x8000000F)
	addi		$t1, $t0, -16
	TEST_EXPECT	$t1, 0x7FFFFFFF

	# ################################################################

	# Test with $zero as destination
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	addi		$zero, $t0, 16
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
