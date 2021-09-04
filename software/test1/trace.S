addiu   $1, $0, 0x3fff
addiu   $2, $0, 0xabcd
addu    $3, $1, $2
sw      $3, 4($0)
lw      $4, 4($0)