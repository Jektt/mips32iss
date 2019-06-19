	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test zero value

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	ori		$t1, $t0, 0
	TEST_EXPECT	$t1, 0x5A5A5A5A

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	ori		$t1, $t0, 0
	TEST_EXPECT	$t1, 0xA5A5A5A5

	# Test positive value

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	ori		$t1, $t0, 0x00FF
	TEST_EXPECT	$t1, 0x5A5A5AFF

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	ori		$t1, $t0, 0x00FF
	TEST_EXPECT	$t1, 0xA5A5A5FF

	# Test negative value, zero extended

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	ori		$t1, $t0, 0xF00F
	TEST_EXPECT	$t1, 0x5A5AFA5F

	lui		$t0, %hi(0xA5A5A5A5)
	addi		$t0, $t0, %lo(0xA5A5A5A5)
	ori		$t1, $t0, 0xF00F
	TEST_EXPECT	$t1, 0xA5A5F5AF

	# ################################################################

	# Test with $zero as destination

	lui		$t0, %hi(0x5A5A5A5A)
	addi		$t0, $t0, %lo(0x5A5A5A5A)
	ori		$zero, $t0, 0x00F
	TEST_EXPECT	$zero, 0x00000000
	

	TEST_END
