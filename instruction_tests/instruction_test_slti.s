	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# ################################################################
	# True result

	# positive arguments

	lui		$s0, %hi(1000)
	addi		$s0, $s0, %lo(1000)
	slti		$s2, $s0, 2000
	TEST_EXPECT	$s2, 1

	# negative arguments

	lui		$s0, %hi(-2000)
	addi		$s0, $s0, %lo(-2000)
	slti		$s2, $s0, -1000
	TEST_EXPECT	$s2, 1
	
	# negative/positive arguments

	lui		$s0, %hi(-1000)
	addi		$s0, $s0, %lo(-1000)
	slti		$s2, $s0, 1000
	TEST_EXPECT	$s2, 1

	# zero/positive arguments

	lui		$s0, %hi(0)
	addi		$s0, $s0, %lo(0)
	slti		$s2, $s0, 1000
	TEST_EXPECT	$s2, 1

	# negative/zero arguments

	lui		$s0, %hi(-1000)
	addi		$s0, $s0, %lo(-1000)
	slti		$s2, $s0, 0
	TEST_EXPECT	$s2, 1
	

	# ################################################################
	# False result

	# positive arguments

	lui		$s0, %hi(2000)
	addi		$s0, $s0, %lo(2000)
	slti		$s2, $s0, 1000
	TEST_EXPECT	$s2, 0

	# negative arguments

	lui		$s0, %hi(-1000)
	addi		$s0, $s0, %lo(-1000)
	slti		$s2, $s0, -2000
	TEST_EXPECT	$s2, 0
	
	# positive/negative arguments
	
	lui		$s0, %hi(1000)
	addi		$s0, $s0, %lo(1000)
	slti		$s2, $s0, -1000
	TEST_EXPECT	$s2, 0
	
	# positive/zero arguments

	lui		$s0, %hi(1000)
	addi		$s0, $s0, %lo(1000)
	slti		$s2, $s0, 0
	TEST_EXPECT	$s2, 0
	
	# zero/negative arguments

	lui		$s0, %hi(0)
	addi		$s0, $s0, %lo(0)
	slti		$s2, $s0, -1000
	TEST_EXPECT	$s2, 0
	
	# equal positive

	lui		$s0, %hi(1000)
	addi		$s0, $s0, %lo(1000)
	slti		$s2, $s0, 1000
	TEST_EXPECT	$s2, 0
	
	# equal negative

	lui		$s0, %hi(-1000)
	addi		$s0, $s0, %lo(-1000)
	slti		$s2, $s0, -1000
	TEST_EXPECT	$s2, 0
	
	# equal zero

	lui		$s0, %hi(0)
	addi		$s0, $s0, %lo(0)
	slti		$s2, $s0, 0
	TEST_EXPECT	$s2, 0
	

	TEST_END
	
