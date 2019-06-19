	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	addi		$s0, $zero, 0

	# Forward jump
	
L1:	j		L1_t
	addi		$s0, $zero, 1
	TEST_FAIL
L1_t:	TEST_EXPECT	$s0, 1

	# Jump over target for backward jump

L2:	j		L2_t
	addi		$s0, $zero, 2
	TEST_FAIL

	# Target for backward jump

L3_t:	TEST_EXPECT	$s0, 3
	
	TEST_END

	# Target for forward jump

L2_t:	TEST_EXPECT	$s0, 2

	# Backward jump

L3:	j		L3_t
	addi		$s0, $zero, 3
	TEST_FAIL
