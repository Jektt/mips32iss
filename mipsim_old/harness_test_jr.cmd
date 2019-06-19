# Test with pc[31:28] = 0x0

$8 = 00800000
m 00002000 = 01000008  # jr $8
m 00002004 = 00000000  # nop in delay slot
pc = 00002000
.
pc	# expect 0x00002004
.
pc	# expect 0x00800000
$8	# expect 0x00800000

# Test with pc[31:28] = 0x3

$8 = 00600000
m 30003000 = 01000008  # jr $8
m 30003004 = 00000000  # nop in delay slot
pc = 30003000
.
pc	# expect 0x30003004
.
pc	# expect 0x30600000
$8	# expect 0x00600000

