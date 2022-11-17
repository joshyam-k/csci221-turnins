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
    beq $t2, $zero, Extract    # if i >= n then move on to extraction step
    slli $t3, $t0, 3        # $t3 = 8*i
    add $t4, $a0, $t3       # $t5 = array + 8*i
    lwcl $f2, 0($t5)        # $f0 = array[i]
    add.d $f0, $f0, $f2     # add to total
    j add_array
Extract:
    mfcl $a0, $f0     # put total into argument registers
    mfcl $a1, $f1
    and $t5, $a0, 0x7F800000      # 0111|1111|1000| 0-0-0-0-0
    slr $t5, $t5, 52  # shift so lsb of exponent encoding is lsb of return value
    j Exit
Exit:
    li $v0, 10
    syscall

    
    
