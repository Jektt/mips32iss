../../mipsim ${MIPSIM_FLAGS} -ds 8 -db 16 -da 2 -dwt > output.txt <<'EOF'

m 80000000 = 8F000000
m 80001000 = 8F001000
m 80004000 = 8F004000
m 80005000 = 8F005000

m 0000 = 8c220000  # lw $2, 0000($1)

pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from 2 locations each mapping to set 0.
# Expect cold-start misses.

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

$1 = 80001000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from another location mapping to set 0.
# Expect miss with replacement of LRU entry (address 80000000).

$1 = 80004000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from non-replaced entries, expect hit.

$1 = 80001000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from replaced address, expect miss.

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from another location mapping to set 0.
# Expect miss with replacement of LRU entry (address 80001000).

$1 = 80005000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from non-replaced entries, expect hit.

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000

# Read from replaced address, expect miss.

$1 = 80001000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80004000
pd 80005000


EOF
