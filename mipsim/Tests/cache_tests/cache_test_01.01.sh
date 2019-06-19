../../mipsim ${MIPSIM_FLAGS} -is 64 -ib 16 -ia 1 > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 0100 = 20000100 # addi $0, $0, 0100
m 0200 = 20000200 # addi $0, $0, 0200
m 0300 = 20000300 # addi $0, $0, 0300

pi 0000
pi 0100
pi 0200
pi 0300

pc = 0000
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0100
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0200
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0300
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0000
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0100
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0200
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0300
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0000
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0100
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0200
.
pi 0000
pi 0100
pi 0200
pi 0300

pc = 0300
.
pi 0000
pi 0100
pi 0200
pi 0300


EOF
