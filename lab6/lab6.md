# 1

(a)

Because this function only uses the standard registers as arguments and standard registers as outputs and doesn't call another function, we don't need to add a stack to our frame or anything like that.

```
function:
    procedure using $a0-$a3 and putting things in registers $v0-$v1
    jr $ra
```

(b)

This time since func1 calls func2 and we want the procedure to run in a seamless manner, we need to allocate space for the frame, save the callee-saved registers, and set the frame pointer in func1. Then we need to restore the callee saved registers that we stored earlier, pop the frame, and then return with `jr $ra`.  

```
func1:
    # function body
    addiu $sp, $sp, -32     # push frame
    sw $ra, 28($sp)         # store $ra
    sw $fp, 24($sp)         # store $fp
    addiu $fp, $sp, 28      # set new $fp
    jal func2               # jump and link func2
    lw $fp, 24($sp)         # load $fp
    lw $sp, 28($sp)         # load $sp
    addiu $sp, $sp, 32      # pop frame
    jr $ra                  # return
func2:
    procedure
    jr $ra
```

(c)

One big change is that we will need to store and restore the arguments since we don't want to lose those values as they get passed into future stacks in the recursion. So we will need to store and restore `$a0-$a3`

(d)

I don't think that too much will change other than we have to make sure the return values from one function don't get overwritten by return values in another function so we would want to store those things before settingt the `$v0-$v1` registers in another function. It's possible that we would need more than 32 bytes for the frames but not necessarily

(e)

Because we now use `$s0-$s7` which are callee saved, then we need to store these registers before the jal and restore them after we are finished.We also needed to allocate more space for the stack because of all these new callee saved registers in use.

```
func1:
    addiu $sp, $sp, -64
    # function body
    sw $ra, 60($sp)
    sw $fp, 56($sp)
    sw $s0, 52($sp)
    sw $s1, 48($sp)
    sw $s2, 44($sp)
    sw $s3, 40($sp)
    sw $s4, 36($sp)
    sw $s5, 32($sp)
    sw $s6, 28($sp)
    sw $s7, 24($sp)
    addiu $fp, $sp, 60
    jal func2
    lw $s7, 24($sp)
    lw $s6, 28($sp)
    lw $s5, 32($sp)
    lw $s4, 36($sp)
    lw $s3, 40($sp)
    lw $s2, 44($sp)
    lw $s1, 48($sp)
    lw $s0, 52($sp)
    lw $fp, 56($sp)
    lw $sp, 60($sp)
    addiu $sp, $sp, 64
    jr $ra
func2:
    procedure
    jr $ra
```


(f)

We no longer need to use the stack at all.

# 2

Since a tail recursive function returns a call to itself, it might look something like this

```
int foo(n){
    if (n < 1){
        return 1;
    }
    return foo(n-1);
}
```

we can see that since this function just returns a call to itself then we can convert the internals of the function to a loop where we just perform the function internals over and over again until its time to exit

# 3

(a)

```
bltz $s1, $zero, Exit
slti $t0, $s1, 8        # $t0 is 1 if s1 < 8
beq $t0, $zero, Exit    # if s1 >= 8 then exit
slli $t1, $s1, 2        # $t1 = input*4
add $t2, $t1, $s0       # $t2 = input*4 + jumptable_address
lw $t3, 0($t2)          # $t3 = jumptable[input]
jr $t3                  # jump to jumptable[input]
```

(b)

just use inputs as the place to jump to

```

```

(c)

need to map the inputs into 0-7 somehow (charlie says do this as simply as possible)


















