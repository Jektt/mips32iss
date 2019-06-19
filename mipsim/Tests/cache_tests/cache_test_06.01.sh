../../mipsim ${MIPSIM_FLAGS} -is 16 -ib 16 -ia 4 > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 1000 = 20001000 # addi $0, $0, 1000
m 2000 = 20002000 # addi $0, $0, 2000
m 3000 = 20003000 # addi $0, $0, 3000
m 4000 = 20004000 # addi $0, $0, 4000
m 0010 = 20000010 # addi $0, $0, 0010
m 1010 = 20001010 # addi $0, $0, 1010
m 2010 = 20002010 # addi $0, $0, 2010
m 3010 = 20003010 # addi $0, $0, 3010
m 4010 = 20004010 # addi $0, $0, 4010

pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from 4 locations each mapping to set 0.

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 1000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 2000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 3000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from entry 0 in set 0, making entry 1 LRU.

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from 4 locations each mapping to set 1.

pc = 0010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 1010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 2010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 3010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from entries 0, 1, 2 in set 1, making entry 3 LRU.

pc = 0010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 1010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 2010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from another location mapping to set 0, entry 1 replaced.

pc = 4000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from another location mapping to set 1, entry 3 replaced.

pc = 4010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from entries 0, 2, 3 in set 0, expect all hits.

pc = 0000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 2000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 3000
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

# Read from entries 0, 1, 2 in set 1, expect all hits.

pc = 0010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 1010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

pc = 2010
.
pi 0000
pi 1000
pi 2000
pi 3000
pi 4000
pi 0010
pi 1010
pi 2010
pi 3010
pi 4010

EOF
