# Test SPIM syntax
.data
.align 2
b: .space 36
.align 2
a: .space 36

.text
.globl main

main:
    li $v0, 10
    syscall
