../../mipsim ${MIPSIM_FLAGS} -is 1 -ib 64 -ia 2 > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 1000 = 20001000 # addi $0, $0, 1000

pi 0000
pi 1000

pc = 0000
.
pi 0000
pi 1000

pc = 1000
.
pi 0000
pi 1000

pc = 0000
.
pi 0000
pi 1000

pc = 1000
.
pi 0000
pi 1000

EOF
