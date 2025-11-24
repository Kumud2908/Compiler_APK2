testcase1:
    i = 42
    f = 3
    c = 'A'
    param "\nTESTCASE 1: printf basic types\n"
    t0 = call printf, 1
    param "Integer: %d\n"
    param i
    t1 = call printf, 2
    param "Float: %f\n"
    param f
    t2 = call printf, 2
    param "Character: %c\n"
    param c
    t3 = call printf, 2
    return
testcase2:
    a = 10
    b = 20
    t4 = a + b
    sum = t4
    param "\nTESTCASE 2: printf multiple values\n"
    t5 = call printf, 1
    param "%d + %d = %d\n"
    param a
    param b
    param sum
    t6 = call printf, 4
    return
testcase3:
    param "\nTESTCASE 3: scanf with integer\n"
    t7 = call printf, 1
    param "Enter an integer: "
    t8 = call printf, 1
    param "%d"
    t9 = &num
    param t9
    t10 = call scanf, 2
    param "You entered: %d\n"
    t11 = num[0]
    param t11
    t12 = call printf, 2
    return
testcase4:
    param "\nTESTCASE 4: scanf multiple integers\n"
    t13 = call printf, 1
    param "Enter three integers: "
    t14 = call printf, 1
    param "%d %d %d"
    t15 = &a
    param t15
    t16 = &b
    param t16
    t17 = &c
    param t17
    t18 = call scanf, 4
    param "You entered: %d, %d, %d\n"
    t19 = a[0]
    param t19
    t20 = b[0]
    param t20
    t21 = c[0]
    param t21
    t22 = call printf, 4
    return
testcase5:
    t23 = &x
    ptr = t23
    param "\nTESTCASE 5: scanf with pointer\n"
    t24 = call printf, 1
    param "Enter value via pointer: "
    t25 = call printf, 1
    param "%d"
    param ptr
    t26 = call scanf, 2
    param "Value: %d\n"
    t27 = *ptr
    param t27
    t28 = call printf, 2
    return
testcase6:
    param "\nTESTCASE 6: scanf in loop\n"
    t29 = call printf, 1
    param "Enter 3 numbers:\n"
    t30 = call printf, 1
    i = 0
L0:
    t31 = i < 3
    ifFalse t31 goto L1
    param "Number %d: "
    t32 = i + 1
    param t32
    t33 = call printf, 2
    param "%d"
    t35 = &nums
    t36 = i * 4
    t34 = t35 + t36
    param t34
    t37 = call scanf, 2
L2:
    t38 = i
    i = i + 1
    goto L0
L1:
    param "You entered: "
    t39 = call printf, 1
    i = 0
L3:
    t40 = i < 3
    ifFalse t40 goto L4
    param "%d "
    t41 = i * 4
    t42 = &nums
    t43 = t42 + t41
    t44 = *t43
    param t44
    t45 = call printf, 2
L5:
    t46 = i
    i = i + 1
    goto L3
L4:
    param "\n"
    t47 = call printf, 1
    return
main:
    param "=================================\n"
    t48 = call printf, 1
    param "PRINTF/SCANF TEST SUITE\n"
    t49 = call printf, 1
    param "=================================\n"
    t50 = call printf, 1
    call testcase1, 0
    call testcase2, 0
    param "\nAll printf/scanf tests completed!\n"
    t51 = call printf, 1
    return 0
