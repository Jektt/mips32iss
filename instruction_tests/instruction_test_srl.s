	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test positive value, zero shift
	lui		$t0, %hi(0x5A6B7C8D)
	addi		$t0, $t0, %lo(0x5A6B7C8D)
	srl		$t1, $t0, 0
	TEST_EXPECT	$t1, 0x5A6B7C8D

	# Test positive value, non-zero shift
	lui		$t0, %hi(0x5A6B7C8D)
	addi		$t0, $t0, %lo(0x5A6B7C8D)
	srl		$t1, $t0, 4
	TEST_EXPECT	$t1, 0x5A6B7C8

	# Test positive value, non-zero shift
	lui		$t0, %hi(0x5A6B7C8D)
	addi		$t0, $t0, %lo(0x5A6B7C8D)
	srl		$t1, $t0, 16
	TEST_EXPECT	$t1, 0x00005A6B

	# Test negative value, zero shift
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	srl		$t1, $t0, 0
	TEST_EXPECT	$t1, 0xA5B6C7D8

	# Test negative value, non-zero shift
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	srl		$t1, $t0, 4
	TEST_EXPECT	$t1, 0x0A5B6C7D

	# Test negative value, non-zero shift
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	srl		$t1, $t0, 16
	TEST_EXPECT	$t1, 0x0000A5B6

	# ################################################################

	# Test with $zero as destination
	lui		$t0, %hi(0xA5B6C7D8)
	addi		$t0, $t0, %lo(0xA5B6C7D8)
	srl		$zero, $t0, 20
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
