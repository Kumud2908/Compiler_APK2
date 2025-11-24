main:
    t0 = &d
    *t0 = 65
    param "i = %d\n"
    t1 = &d
    t2 = *t1
    param t2
    t3 = call printf, 2
    t4 = &d
    *t4 = 'A'
    param "c = %c, i = %d\n"
    t5 = &d
    t6 = *t5
    param t6
    t7 = &d
    t8 = *t7
    param t8
    t9 = call printf, 3
    t10 = &d
    *t10 = 3.14
    param "f = %.2f, i = %d\n"
    t11 = &d
    t12 = *t11
    param t12
    t13 = &d
    t14 = *t13
    param t14
    t15 = call printf, 3
    return 0
