	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test zero value
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	xor		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0x5A5A5A5A

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	xor		$t2, $t0, $zero
	TEST_EXPECT	$t2, 0xA5A5A5A5

	lui		$t1, %hi(0x5A5A5A5A)
	addi		$t1, $t1, %lo(0x5A5A5A5A)
	xor		$t2, $zero, $t1
	TEST_EXPECT	$t2, 0x5A5A5A5A

	lui		$t1, %hi(0xA5A5A55A)
	addi		$t1, $t1, %lo(0xA5A5A5A5)
	xor		$t2, $zero, $t1
	TEST_EXPECT	$t2, 0xA5A5A5A5

	# Test non-zero values
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	xor		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0x5555AAAA

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	xor		$t2, $t0, $t1
	TEST_EXPECT	$t2, 0xAAAA5555

	# ################################################################

	# Test with $zero as destination
	
	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	lui		$t1, %hi(0x0F0FF0F0)
	addi		$t1, $t1, %lo(0x0F0FF0F0)
	xor		$zero, $t0, $t1
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
