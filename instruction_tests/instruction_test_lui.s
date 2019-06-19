	.include "test_defines.h"

	.text
	.align	2
	
	.globl	__start
__start:

	TEST_INIT

	# Test positive value
	lui		$t0, 0x0001
	TEST_EXPECT	$t0, 0x00010000

	# Test positive value
	lui		$t1, 0x5A6B
	TEST_EXPECT	$t1, 0x5A6B0000

	# Test negative value
	lui		$t2, 0xA5B6
	TEST_EXPECT	$t2, 0xA5B60000

	# Test value overwrites previous content
	lui		$t4, 0xAAAA
	addi            $t4, $t4, 0x5555
	TEST_EXPECT	$t4, 0xAAAA5555
	lui		$t4, 0x0000
	TEST_EXPECT	$t4, 0x00000000

	TEST_END
