	.set noreorder

	.macro  TEST_INIT
	addi	$v0, $0, 0
	.endm

	.macro  TEST_EXPECT _r, _v
	lui	$v1, %hi(\_v)
	addi	$v1, $v1, %lo(\_v)
	bne	\_r, $v1, _test_finish
        nop
	.endm

        .macro  TEST_FAIL
	addi	$v0, $0, 0
	jr	$0
        nop
	.endm

	.macro  TEST_END
	addi	$v0, $0, 1
_test_finish:
	jr	$0
        nop
	.endm

