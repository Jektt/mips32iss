../../mipsim ${MIPSIM_FLAGS} -is 8 -ib 16 -ia 2 > output.txt <<EOF

m 0000 = 20000000 # addi $0, $0, 0000
m 1000 = 20001000 # addi $0, $0, 1000
m 4000 = 20004000 # addi $0, $0, 4000
m 5000 = 20005000 # addi $0, $0, 5000

pi 0000
pi 1000
pi 4000
pi 5000

# Read from 2 locations each mapping to set 0.
# Expect cold-start misses.

pc = 0000
.
pi 0000
pi 1000
pi 4000
pi 5000

pc = 1000
.
pi 0000
pi 1000
pi 4000
pi 5000

# Read from another location mapping to set 0.
# Expect miss with replacement of LRU entry (address 0000).

pc = 4000
.
pi 0000
pi 1000
pi 4000
pi 5000

# Read from non-replaced entries, expect hit.

pc = 1000
.
pi 0000
pi 1000
pi 4000
pi 5000

# Read from replaced address, expect miss.

pc = 0000
.
pi 0000
pi 1000
pi 4000
pi 5000

# Read from another location mapping to set 0.
# Expect miss with replacement of LRU entry (address 1000).

pc = 5000
.
pi 0000
pi 1000
pi 4000
pi 5000

# Read from non-replaced entries, expect hit.

pc = 0000
.
pi 0000
pi 1000
pi 4000
pi 5000

# Read from replaced address, expect miss.

pc = 1000
.
pi 0000
pi 1000
pi 4000
pi 5000

EOF
