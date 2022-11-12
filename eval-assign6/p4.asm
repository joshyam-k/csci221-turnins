.data
list: .float 1.1, 2.1, 3.1, 4.1, 5.1
.text
.globl main
main:
    li.d $f0, 2.5
    la $a0, list    # put address of array into a0
    li $t0, 0       # index (i = 0)
    li $t1, 5       # length of list
add_array:
    slt $t2, $t0, $t1       # 1 if i < n
    beq $t2, $zero, Exit    # if i >= n then exit
    slli $t3, $t0, 2        # $t3 = 4*i
    add $t4, $a0, $t3       # $t5 = array + 4*i
    lwcl $f1, 0($t5)        # $f0 = array[i]
    add.d $f0, $f1
    j add_array
Exit:
    li $v0, 10
    syscall

    
    
