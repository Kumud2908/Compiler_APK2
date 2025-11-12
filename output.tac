main:
    t0 = &a
    *t0 = 1
    t1 = t0 + 4
    *t1 = 2
    t2 = t0 + 8
    *t2 = 3
    t3 = t0 + 12
    *t3 = 4
    t4 = t0 + 16
    *t4 = 5
    t5 = t0 + 20
    *t5 = 6
    t6 = t0 + 24
    *t6 = 7
    t7 = t0 + 28
    *t7 = 8
    t8 = t0 + 32
    *t8 = 9
    i = 0
L0:
    t9 = i < 3
    ifFalse t9 goto L1
    j = 0
L3:
    t10 = j < 3
    ifFalse t10 goto L4
    t11 = i * 3
    t12 = t11 + j
    t13 = t12 * 4
    t14 = &a
    t15 = t14 + t13
    t16 = *t15
    t17 = j * 3
    t18 = t17 + i
    t19 = t18 * 4
    t20 = &b
    t21 = t20 + t19
    *t21 = t16
L5:
    t22 = j
    j = j + 1
    goto L3
L4:
L2:
    t23 = i
    i = i + 1
    goto L0
L1:
    i = 0
L6:
    t24 = i < 3
    ifFalse t24 goto L7
    j = 0
L9:
    t25 = j < 3
    ifFalse t25 goto L10
    param "%d "
    t26 = i * 3
    t27 = t26 + j
    t28 = t27 * 4
    t29 = &b
    t30 = t29 + t28
    t31 = *t30
    param t31
    t32 = call printf, 2
L11:
    t33 = j
    j = j + 1
    goto L9
L10:
    param "\n"
    t34 = call printf, 1
L8:
    t35 = i
    i = i + 1
    goto L6
L7:
    return 0
