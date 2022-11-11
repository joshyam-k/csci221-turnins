.text
.globl main
main:
   # in C:
   # struct node {
   #    int val;
   #    struct node* next;
   # };
   # data is offset 0 from the pointer
   # next is offset 4 from the pointer
   # $a0 holds the pointer to the first node
   li $t0, 0    # this will hold the sum
loop:
    beqz $a0, Exit  # if the pointer is zero then exit
    lh $t1, 0($a0)  # load the 16bit integer offset 0 from the head pointer
    add $t0, $t0, $t1   # add that value to the sum
    lw $a0, 4($a0)  # set the head pointer to point to the next node
    j loop          # return to the top of the loop
Exit:
    li $v0, 10
    syscall
    

