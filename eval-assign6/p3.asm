.data
arr_char: .space 40
sun: .asciiz "sunday\0"
mon: .asciiz "monday\0"
tue: .asciiz "tuesday\0"
wed: .asciiz "wednesday\0"
thu: .asciiz "thursday\0"
fri: .asciiz "friday\0"
sat: .asciiz "saturday\0"
JumpTable: 
    .word L0
    .word L1
    .word L2
    .word L3
    .word L4
    .word L5
    .word L6
.text
.globl main
main:
la $t0 JumpTable
la $a1 arr_char
li $a0 4
bltz $a0, Exit
slti $t1, $a0, 6
bew $t1, $zero, Exit
slli $t2, $a0, 2      # code*4
add $t3, $t2, $t0   
lw $t4, 0($t3)      # $t4 = JumpTable[code]
jr $t4
L0: 
    # Sunday
    la $a2, sun
    j Loop
L1:
    # Monday
    la $a2, mon
    j Loop
L2:
    # Tuesday
    la $a2 tue
    j Loop
L3:
    # Wednesda
    la $a2 wed
    j Loop
L4:
    # Thursday
    la $a2 thu
    j Loop
L5:
    # Friday
    la $a2 fri
    j Loop
L6:
    # Saturday
    la $a2 sat
    j Loop
Loop:
   lw $t5, 0($a2)
   sw $t5 0($a1)
   beqz $t5, Exit
   addi $a1, $a1, 4
   addi $a2, $a2, 4
   j Loop
Exit:
    li $v0, 10
    
