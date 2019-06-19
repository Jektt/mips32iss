../../mipsim ${MIPSIM_FLAGS} -is 1 -ib 64 -ia 4 > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 1000 = 20001000 # addi $0, $0, 1000
m 2000 = 20002000 # addi $0, $0, 2000
m 3000 = 20003000 # addi $0, $0, 3000

pi 0000
pi 1000
pi 2000
pi 3000

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 1000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 2000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 3000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 1000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 2000
.
pi 0000
pi 1000
pi 2000
pi 3000

pc = 3000
.
pi 0000
pi 1000
pi 2000
pi 3000

EOF
