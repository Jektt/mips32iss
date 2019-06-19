	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# ################################################################
	# True result

	# positive arguments

	lui		$s0, %hi(0x05A5A5A5)
	addi		$s0, $s0, %lo(0x05A5A5A5)
	lui		$s1, %hi(0x0A5A5A5A)
	addi		$s1, $s1, %lo(0x0A5A5A5A)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 1

	# negative arguments

	lui		$s0, %hi(0xA5A5A5A5)
	addi		$s0, $s0, %lo(0xA5A5A5A5)
	lui		$s1, %hi(0xAA55AA55)
	addi		$s1, $s1, %lo(0xAA55AA55)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 1
	
	# negative/positive arguments

	lui		$s0, %hi(0xA5A5A5A5)
	addi		$s0, $s0, %lo(0xA5A5A5A5)
	lui		$s1, %hi(0x5A5A5A5A)
	addi		$s1, $s1, %lo(0x5A5A5A5A)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 1

	# zero/positive arguments

	lui		$s0, %hi(0x00000000)
	addi		$s0, $s0, %lo(0x00000000)
	lui		$s1, %hi(0x5A5A5A5A)
	addi		$s1, $s1, %lo(0x5A5A5A5A)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 1

	# negative/zero arguments

	lui		$s0, %hi(0xA5A5A5A5)
	addi		$s0, $s0, %lo(0xA5A5A5A5)
	lui		$s1, %hi(0x00000000)
	addi		$s1, $s1, %lo(0x00000000)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 1
	

	# ################################################################
	# False result

	# positive arguments

	lui		$s0, %hi(0x0A5A5A5A)
	addi		$s0, $s0, %lo(0x0A5A5A5A)
	lui		$s1, %hi(0x05A5A5A5)
	addi		$s1, $s1, %lo(0x05A5A5A5)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0

	# negative arguments

	lui		$s0, %hi(0xAA55AA55)
	addi		$s0, $s0, %lo(0xAA55AA55)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	
	# positive/negative arguments
	
	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	
	# positive/zero arguments

	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0x00000000)
	addi		$s1, $s1, %lo(0x00000000)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	
	# zero/negative arguments

	lui		$s0, %hi(0x00000000)
	addi		$s0, $s0, %lo(0x00000000)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	
	# equal positive

	lui		$s0, %hi(0x5A5A5A5A)
	addi		$s0, $s0, %lo(0x5A5A5A5A)
	lui		$s1, %hi(0x5A5A5A5A)
	addi		$s1, $s1, %lo(0x5A5A5A5A)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	
	# equal negative

	lui		$s0, %hi(0xA5A5A5A5)
	addi		$s0, $s0, %lo(0xA5A5A5A5)
	lui		$s1, %hi(0xA5A5A5A5)
	addi		$s1, $s1, %lo(0xA5A5A5A5)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	
	# equal zero

	lui		$s0, %hi(0x00000000)
	addi		$s0, $s0, %lo(0x00000000)
	lui		$s1, %hi(0x00000000)
	addi		$s1, $s1, %lo(0x00000000)
	slt		$s2, $s0, $s1
	TEST_EXPECT	$s2, 0
	

	TEST_END
	
