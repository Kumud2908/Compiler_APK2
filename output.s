    # ==============================================
    #   MIPS Assembly Code
    #   Generated from Three-Address Code
    # ==============================================

.data
.align 2
str_2: .asciiz "f = %.2f, i = %d\n"
.align 2
str_1: .asciiz "c = %c, i = %d\n"
.align 2
str_0: .asciiz "i = %d\n"
.align 2
newline: .asciiz "\n"
.align 2
var_d: .space 400

.text
.globl main


    # Function: main
main:
    # Reserve stack space for register spills
    addi $sp, $sp, -256
    la $t0, var_d
    li $t1, 65
    sw $t1, 0($t0)
    la $s0, str_0
    # Save string param str_0 to $s0
    la $t1, var_d
    lw $t2, 0($t1)
    move $s1, $t2
    # Save param t2 to $s1
    # Call printf
    li $v0, 11
    li $a0, 105
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 61
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    # Print integer
    li $v0, 1
    move $a0, $s1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    la $t0, var_d
    li $t1, 65
    sw $t1, 0($t0)
    la $s2, str_1
    # Save string param str_1 to $s2
    la $t1, var_d
    lw $t2, 0($t1)
    move $s3, $t2
    # Save param t6 to $s3
    la $t1, var_d
    lw $t2, 0($t1)
    move $s4, $t2
    # Save param t8 to $s4
    # Call printf
    li $v0, 11
    li $a0, 99
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 61
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    # Print character
    li $v0, 11
    move $a0, $s3
    syscall
    li $v0, 11
    li $a0, 44
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 105
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 61
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    # Print integer
    li $v0, 1
    move $a0, $s4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    la $t0, var_d
    sw $t1, 0($t0)
    la $s5, str_2
    # Save string param str_2 to $s5
    la $t2, var_d
    lw $t3, 0($t2)
    move $s6, $t3
    # Save param t12 to $s6
    la $t2, var_d
    lw $t3, 0($t2)
    move $s7, $t3
    # Save param t14 to $s7
    # Call printf
    li $v0, 11
    li $a0, 102
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 61
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    # Print float
    # Print float
    li $v0, 2
    mtc1 $s6, $f12
    syscall
    li $v0, 11
    li $a0, 44
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 105
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    li $v0, 11
    li $a0, 61
    syscall
    li $v0, 11
    li $a0, 32
    syscall
    # Print integer
    li $v0, 1
    move $a0, $s7
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $v0, 0
    # Restore stack and exit program
    addi $sp, $sp, 256
    li $v0, 10
    syscall
