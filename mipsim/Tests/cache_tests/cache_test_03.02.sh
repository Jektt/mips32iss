../../mipsim ${MIPSIM_FLAGS} -is 1 -ib 512 -ia 1 > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 0100 = 20000100 # addi $0, $0, 0100
m 0200 = 20000200 # addi $0, $0, 0200
m 0300 = 20000300 # addi $0, $0, 0300
m 0400 = 20000400 # addi $0, $0, 0400
m 0500 = 20000500 # addi $0, $0, 0500
m 0600 = 20000600 # addi $0, $0, 0600
m 0700 = 20000700 # addi $0, $0, 0700
m 0800 = 20000800 # addi $0, $0, 0800
m 0900 = 20000900 # addi $0, $0, 0900
m 0a00 = 20000a00 # addi $0, $0, 0a00
m 0b00 = 20000b00 # addi $0, $0, 0b00
m 0c00 = 20000c00 # addi $0, $0, 0c00
m 0d00 = 20000d00 # addi $0, $0, 0d00
m 0e00 = 20000e00 # addi $0, $0, 0e00
m 0f00 = 20000f00 # addi $0, $0, 0f00

pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0000
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0100
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0200
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0300
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0400
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0500
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0600
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0700
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0800
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0900
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0a00
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0b00
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0c00
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0d00
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0e00
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

pc = 0f00
.
pi 0000
pi 0100
pi 0200
pi 0300
pi 0400
pi 0500
pi 0600
pi 0700
pi 0800
pi 0900
pi 0a00
pi 0b00
pi 0c00
pi 0d00
pi 0e00
pi 0f00

EOF
