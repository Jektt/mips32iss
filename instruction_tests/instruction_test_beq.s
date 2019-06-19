	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	addi		$t0, $zero, 0

	# Test branch taken, positive displacement

	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0x5A5A5A5A)
	addi		$s1, $s1, %lo(0x5A5A5A5A)
	beq		$s0, $s1, L1_t
	addi		$t0, $zero, 1
	TEST_FAIL
L1_t:	TEST_EXPECT	$t0, 1

	lui		$s2, %hi(0xA5A5A5A5)
	addi		$s2, $s2, %lo(0xA5A5A5A5)
	lui		$s3, %hi(0xA5A5A5A5)
	addi		$s3, $s3, %lo(0xA5A5A5A5)
	beq		$s2, $s3, L2_t
	addi		$t0, $zero, 2
	TEST_FAIL
L2_t:	TEST_EXPECT	$t0, 2

	# Test branch not taken, positive displacement

	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	beq		$s0, $s1, L3_t
	addi		$t0, $zero, 3
	j		L3
	nop
L3_t:	
	TEST_FAIL
L3:	TEST_EXPECT	$t0, 3
	
	lui		$s2, %hi(0x5A5A5A5A)
	addi		$s2, $s2, %lo(0x5A5A5A5A)
	lui		$s3, %hi(0xA5A5A5A5)
	addi		$s3, $s3, %lo(0xA5A5A5A5)
	beq		$s2, $s3, L4_t
	addi		$t0, $zero, 4
	j		L4
	nop
L4_t:	
	TEST_FAIL
L4:	TEST_EXPECT	$t0, 4
	
	# Test branch taken, negative displacement

	j		L5
	nop
L5_t:	TEST_EXPECT	$t0, 5
	j		L5_e
	nop
L5:	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0x5A5A5A5A)
	addi		$s1, $s1, %lo(0x5A5A5A5A)
	beq		$s0, $s1, L5_t
	addi		$t0, $zero, 5
	TEST_FAIL
L5_e:	

	j		L6
	nop
L6_t:	TEST_EXPECT	$t0, 6
	j		L6_e
	nop
L6:	lui		$s2, %hi(0xA5A5A5A5)
	addi		$s2, $s2, %lo(0xA5A5A5A5)
	lui		$s3, %hi(0xA5A5A5A5)
	addi		$s3, $s3, %lo(0xA5A5A5A5)
	beq		$s2, $s3, L6_t
	addi		$t0, $zero, 6
	TEST_FAIL
L6_e:	

	# Test branch not taken, negative displacement

	j		L7
	nop
L7_t:
	TEST_FAIL
L7:	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	beq		$s0, $s1, L7_t
	addi		$t0, $zero, 7
	TEST_EXPECT	$t0, 7

	j		L8
	nop
L8_t:
	TEST_FAIL
L8:	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	beq		$s0, $s1, L8_t
	addi		$t0, $zero, 8
	TEST_EXPECT	$t0, 8
	
	TEST_END
	
