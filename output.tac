test_postfix_increment:
    t0 = &arr
    *t0 = 10
    t1 = t0 + 4
    *t1 = 20
    t2 = t0 + 8
    *t2 = 30
    t3 = t0 + 12
    *t3 = 40
    t4 = t0 + 16
    *t4 = 50
    p = arr
    param "Test 1: Postfix increment (ptr++)\n"
    t5 = call printf, 1
    param "Initial: *p = %d\n"
    t6 = *p
    param t6
    t7 = call printf, 2
    t8 = p
    p = p + 1
    param "After p++: *p = %d\n"
    t9 = *p
    param t9
    t10 = call printf, 2
    t11 = p
    p = p + 1
    param "After p++: *p = %d\n"
    t12 = *p
    param t12
    t13 = call printf, 2
    param "\nTest 2: Postfix decrement (ptr--)\n"
    t14 = call printf, 1
    t15 = p
    p = p - 1
    param "After p--: *p = %d\n"
    t16 = *p
    param t16
    t17 = call printf, 2
    t18 = p
    p = p - 1
    param "After p--: *p = %d\n"
    t19 = *p
    param t19
    t20 = call printf, 2
    return
test_pointer_arithmetic:
    t21 = &nums
    *t21 = 5
    t22 = t21 + 4
    *t22 = 15
    t23 = t21 + 8
    *t23 = 25
    t24 = t21 + 12
    *t24 = 35
    t25 = t21 + 16
    *t25 = 45
    ptr = nums
    param "\nTest 3: Combining ptr++ with dereference\n"
    t26 = call printf, 1
    param "*ptr++ would be: %d (though we test sequentially)\n"
    t27 = *ptr
    param t27
    t28 = call printf, 2
    t29 = ptr
    ptr = ptr + 1
    param "After increment: *ptr = %d\n"
    t30 = *ptr
    param t30
    t31 = call printf, 2
    param "\nTest 4: Array access with ptr++ in loop\n"
    t32 = call printf, 1
    ptr2 = nums
    i = 0
L0:
    t33 = i < 5
    ifFalse t33 goto L1
    param "nums[%d] = %d\n"
    param i
    t34 = *ptr2
    param t34
    t35 = call printf, 3
    t36 = ptr2
    ptr2 = ptr2 + 1
L2:
    t37 = i
    i = i + 1
    goto L0
L1:
    return
main:
    call test_postfix_increment, 0
    call test_pointer_arithmetic, 0
    param "\nAll tests passed!\n"
    t38 = call printf, 1
    return 0
