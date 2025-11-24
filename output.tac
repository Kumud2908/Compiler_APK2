main:
    t0 = &p
    t1 = t0 + 20
    *t1 = 45
    t2 = &p
    t3 = t2 + 20
    t4 = t3 + 4
    *t4 = 12345
    param "%d %d\n"
    t5 = &p
    t6 = t5 + 20
    t7 = *t6
    param t7
    t8 = &p
    t9 = t8 + 20
    t10 = t9 + 4
    t11 = *t10
    param t11
    t12 = call printf, 3
    return 0
