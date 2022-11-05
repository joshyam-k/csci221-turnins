.text
.globl main
main:
    # importantly the register v0 is reserved for exit values so I store the result at t4
    li $a0, 10
    li $t0, 2  # starting index (we will compare this to n to know when to stop)
    li $t1, 0  # set f_0 = 0
    li $t2, 1     # set f_1 = 1 
    li $t4, 0     # initialize our return value to zero 
loop:
    beq $a0, $zero, Exit
    slt $t3, $a0, $t0      # checking if n < i (eventually want to check i <= n)
    bne $t3, $zero, Exit   # if $t3 = 1 then i > n and so we exit
    add $t4, $t1, $t2      # f_n = f_(n-1) + f_(n-2)
    add $t2, $t1, $zero    # update f_(n-2)
    add $t1, $t4, $zero    # update f_(n-1)
    addi $t0, $t0, 1       # i++
    j loop                 # return to top of loop
Exit:
    li $v0, 10
    syscall
