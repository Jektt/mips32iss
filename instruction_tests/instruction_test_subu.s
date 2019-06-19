	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test positive/zero value
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	subu		$t1, $t0, $zero
	TEST_EXPECT	$t1, 0x5A5A5A5A

	# Test positive/positive value
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(16)
	addi		$t1, $t1, %lo(16)
	subu		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x5A5A5A4A

	# Test positive/negative value, no overflow
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(-16)
	addi		$t1, $t1, %lo(-16)
	subu		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x5A5A5A6A

	# Test positive/negative value, overflow
	lui		$t0, %hi(0x7FFFFFFF)
	addi		$t0, $t0, %lo(0x7FFFFFFF)
	lui		$t1, %hi(-16)
	addi		$t1, $t1, %lo(-16)
	subu		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x8000000F

	# ################################################################

	# Test negative/zero value
	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	subu		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0xA5A5A5A5

	# Test negative/negative value
	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	lui		$t1, %hi(-16)
	addi		$t1, $t1, %lo(-16)
	subu		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0xA5A5A5B5
	
	# Test negative/positive value, no overflow
	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	lui		$t1, %hi(16)
	addi		$t1, $t1, %lo(16)
	subu		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0xA5A5A595

	# Test negative/positive value, overflow
	lui		$t0, %hi(0x8000000F)
	addi		$t0, $t0, %lo(0x8000000F)
	lui		$t1, %hi(16)
	addi		$t1, $t1, %lo(16)
	subu		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x7FFFFFFF

	# ################################################################

	# Test with $zero as destination
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(16)
	addi		$t1, $t1, %lo(16)
	subu		$zero, $t0, $t1
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
