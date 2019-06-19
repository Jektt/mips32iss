	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	addi		$s0, $zero, 0

	# Forward jump
	
	lui		$t0, %hi(L1_t)
	addi		$t0, $t0, %lo(L1_t)
L1:	jr		$t0
	addi		$s0, $zero, 1
	TEST_FAIL
L1_t:	TEST_EXPECT	$s0, 1

	# Jump over target for backward jump

	lui		$t0, %hi(L2_t)
	addi		$t0, $t0, %lo(L2_t)
L2:	jr		$t0
	addi		$s0, $zero, 2
	TEST_FAIL

	# Target for backward jump

L3_t:	TEST_EXPECT	$s0, 3

	TEST_END
	
	# Target for forward jump

L2_t:	TEST_EXPECT	$s0, 2

	# Backward jump

	lui		$t0, %hi(L3_t)
	addi		$t0, $t0, %lo(L3_t)
L3:	jr		$t0
	addi		$s0, $zero, 3
	TEST_FAIL
	
