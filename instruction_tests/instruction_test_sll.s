	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test positive value, zero shift
	lui		$t0, %hi(0x5A6B7C8D)
	addi		$t0, $t0, %lo(0x5A6B7C8D)
	sll		$t1, $t0, 0
	TEST_EXPECT	$t1, 0x5A6B7C8D

	# Test positive value, non-zero shift
	lui		$t0, %hi(0x5A6B7C8D)
	addi		$t0, $t0, %lo(0x5A6B7C8D)
	sll		$t1, $t0, 4
	TEST_EXPECT	$t1, 0xA6B7C8D0

	# Test positive value, non-zero shift
	lui		$t0, %hi(0x5A6B7C8D)
	addi		$t0, $t0, %lo(0x5A6B7C8D)
	sll		$t1, $t0, 16
	TEST_EXPECT	$t1, 0x7C8D0000

	# Test negative value, zero shift
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	sll		$t1, $t0, 0
	TEST_EXPECT	$t1, 0xA5B6C7D8

	# Test negative value, non-zero shift
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	sll		$t1, $t0, 4
	TEST_EXPECT	$t1, 0x5B6C7D80

	# Test negative value, non-zero shift
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	sll		$t1, $t0, 16
	TEST_EXPECT	$t1, 0xC7D80000

	# ################################################################

	# Test with $zero as destination
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	sll		$zero, $t0, 20
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
