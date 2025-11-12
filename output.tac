main:
    x[0] = 10
    y[0] = 20
    t0 = &x
    ptr = t0
    param "x = %d\n"
    t1 = x[0]
    param t1
    t2 = call printf, 2
    param "*ptr = %d\n"
    t3 = *ptr
    param t3
    t4 = call printf, 2
    *ptr = 15
    param "After *ptr = 15, x = %d\n"
    t5 = x[0]
    param t5
    t6 = call printf, 2
    t7 = &y
    ptr = t7
    param "*ptr now points to y = %d\n"
    t8 = *ptr
    param t8
    t9 = call printf, 2
    t10 = &arr
    *t10 = 1
    t11 = t10 + 4
    *t11 = 2
    t12 = t10 + 8
    *t12 = 3
    t13 = t10 + 12
    *t13 = 4
    t14 = t10 + 16
    *t14 = 5
    p = arr
    param "Array elements:\n"
    t15 = call printf, 1
    param "p[0] = %d\n"
    t16 = 0 * 4
    t17 = &p
    t18 = t17 + t16
    t19 = *t18
    param t19
    t20 = call printf, 2
    param "p[1] = %d\n"
    t21 = 1 * 4
    t22 = &p
    t23 = t22 + t21
    t24 = *t23
    param t24
    t25 = call printf, 2
    param "p[2] = %d\n"
    t26 = 2 * 4
    t27 = &p
    t28 = t27 + t26
    t29 = *t28
    param t29
    t30 = call printf, 2
    return 0
