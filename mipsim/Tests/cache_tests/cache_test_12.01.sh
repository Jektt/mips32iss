../../mipsim ${MIPSIM_FLAGS} -ds 16 -db 16 -da 4 -dwt > output.txt <<'EOF'

m 80000000 = 8F000000
m 80001000 = 8F001000
m 80002000 = 8F002000
m 80003000 = 8F003000
m 80004000 = 8F004000
m 80000010 = 8F000010
m 80001010 = 8F001010
m 80002010 = 8F002010
m 80003010 = 8F003010
m 80004010 = 8F004010

m 0000 = 8c220000  # lw $2, 0000($1)

pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from 4 locations each mapping to set 0.

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80001000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80002000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80003000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from entry 0 in set 0, making entry 1 LRU.

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from 4 locations each mapping to set 1.

$1 = 80000010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80001010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80002010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80003010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from entries 0, 1, 2 in set 1, making entry 3 LRU.

$1 = 80000010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80001010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80002010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from another location mapping to set 0, entry 1 replaced.

$1 = 80004000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from another location mapping to set 1, entry 3 replaced.

$1 = 80004010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from entries 0, 2, 3 in set 0, expect all hits.

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80002000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80003000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

# Read from entries 0, 1, 2 in set 1, expect all hits.

$1 = 80000010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80001010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010

$1 = 80002010
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000
pd 80004000
pd 80000010
pd 80001010
pd 80002010
pd 80003010
pd 80004010


EOF
