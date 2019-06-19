	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	addi		$t0, $zero, 0

	# Test branch taken, positive displacement

	lui		$s0, %hi(0xA5A5A5A5)
	addi		$s0, $s0, %lo(0xA5A5A5A5)
	bltz		$s0, L1_t
	addi		$t0, $zero, 1
	TEST_FAIL
L1_t:	TEST_EXPECT	$t0, 1

	# Test branch not taken, positive displacement

	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	bltz		$s0, L2_t
	addi		$t0, $zero, 2
	j		L2
	nop
L2_t:	
	TEST_FAIL
L2:	TEST_EXPECT	$t0, 2
	
	bltz		$zero, L3_t
	addi		$t0, $zero, 3
	j		L3
	nop
L3_t:	
	TEST_FAIL
L3:	TEST_EXPECT	$t0, 3
	
	# Test branch taken, negative displacement

	j		L4
	nop
L4_t:	TEST_EXPECT	$t0, 4
	j		L4_e
	nop
L4:	lui		$s0, %hi(0xA5A5A5A5)
	addi		$s0, $s0, %lo(0xA5A5A5A5)
	bltz		$s0, L4_t
	addi		$t0, $zero, 4
	TEST_FAIL
L4_e:	

	# Test branch not taken, negative displacement

	j		L5
	nop
L5_t:
	TEST_FAIL
L5:	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	bltz		$s0, L5_t
	addi		$t0, $zero, 5
	TEST_EXPECT	$t0, 5

	j		L6
	nop
L6_t:
	TEST_FAIL
L6:	bltz		$zero, L6_t
	addi		$t0, $zero, 6
	TEST_EXPECT	$t0, 6
	
	TEST_END
	
