	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test zero value

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	andi		$t1, $t0, 0
	TEST_EXPECT	$t1, 0x00000000

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	andi		$t1, $t0, 0
	TEST_EXPECT	$t1, 0x00000000

	# Test positive value

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	andi		$t1, $t0, 0x00FF
	TEST_EXPECT	$t1, 0x0000005A

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	andi		$t1, $t0, 0x00FF
	TEST_EXPECT	$t1, 0x000000A5

	# Test negative value, zero extended

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	andi		$t1, $t0, 0xF00F
	TEST_EXPECT	$t1, 0x0000500A

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	andi		$t1, $t0, 0xF00F
	TEST_EXPECT	$t1, 0x0000A005

	# ################################################################

	# Test with $zero as destination

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	andi		$zero, $t0, 0x00F
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
