../../mipsim ${MIPSIM_FLAGS} -ds 1 -db 64 -da 4 -dwt > output.txt <<'EOF'

m 80000000 = 8F000000
m 80001000 = 8F001000
m 80002000 = 8F002000
m 80003000 = 8F003000

m 0000 = 8c220000  # lw $2, 0000($1)

pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80001000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80002000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80003000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80000000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80001000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80002000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000

$1 = 80003000
pc = 0000
.
$2
pd 80000000
pd 80001000
pd 80002000
pd 80003000


EOF
