../../mipsim ${MIPSIM_FLAGS} -is 1 -ib 64 -ia full > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 1000 = 20001000 # addi $0, $0, 1000
m 2000 = 20002000 # addi $0, $0, 2000
m 3000 = 20003000 # addi $0, $0, 3000
m 4000 = 20004000 # addi $0, $0, 4000
m 5000 = 20005000 # addi $0, $0, 5000
m 6000 = 20006000 # addi $0, $0, 6000
m 7000 = 20007000 # addi $0, $0, 7000
m 8000 = 20008000 # addi $0, $0, 8000
m 9000 = 20009000 # addi $0, $0, 9000
m a000 = 2000a000 # addi $0, $0, a000
m b000 = 2000b000 # addi $0, $0, b000
m c000 = 2000c000 # addi $0, $0, c000
m d000 = 2000d000 # addi $0, $0, d000
m e000 = 2000e000 # addi $0, $0, e000
m f000 = 2000f000 # addi $0, $0, f000

pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 1000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 2000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 3000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 4000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 5000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 6000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 7000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 8000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 9000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = a000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = b000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = c000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = d000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = e000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = f000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 1000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 2000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 3000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 4000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 5000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 6000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 7000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 8000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = 9000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = a000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = b000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = c000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = d000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = e000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

pc = f000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 5000
pi 6000
pi 7000
pi 8000
pi 9000
pi a000
pi b000
pi c000
pi d000
pi e000
pi f000

EOF
