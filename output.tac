main:
    t0 = 0 * 3
    t1 = t0 + 0
    t2 = t1 + 0
    t3 = t2 + 0
    a[t3] = 1
    t4 = 0 * 3
    t5 = t4 + 0
    t6 = t5 + 0
    t7 = t6 + 1
    a[t7] = 2
    t8 = 0 * 3
    t9 = t8 + 0
    t10 = t9 + 0
    t11 = t10 + 2
    a[t11] = 3
    t12 = 0 * 3
    t13 = t12 + 1
    t14 = t13 + 0
    t15 = t14 + 0
    a[t15] = 4
    t16 = 0 * 3
    t17 = t16 + 1
    t18 = t17 + 0
    t19 = t18 + 1
    a[t19] = 5
    t20 = 0 * 3
    t21 = t20 + 1
    t22 = t21 + 0
    t23 = t22 + 2
    a[t23] = 6
    t24 = 0 * 3
    t25 = t24 + 2
    t26 = t25 + 0
    t27 = t26 + 0
    a[t27] = 7
    t28 = 0 * 3
    t29 = t28 + 2
    t30 = t29 + 0
    t31 = t30 + 1
    a[t31] = 8
    t32 = 0 * 3
    t33 = t32 + 2
    t34 = t33 + 0
    t35 = t34 + 2
    a[t35] = 9
    i = 0
L0:
    t36 = i < 3
    ifFalse t36 goto L1
    j = 0
L3:
    t37 = j < 3
    ifFalse t37 goto L4
    t38 = i * 3
    t39 = t38 + j
    t40 = a[t39]
    t41 = j * 3
    t42 = t41 + i
    b[t42] = t40
L5:
    t43 = j
    j = j + 1
    goto L3
L4:
L2:
    t44 = i
    i = i + 1
    goto L0
L1:
    i = 0
L6:
    t45 = i < 3
    ifFalse t45 goto L7
    j = 0
L9:
    t46 = j < 3
    ifFalse t46 goto L10
    param "%d "
    t47 = i * 3
    t48 = t47 + j
    t49 = b[t48]
    param t49
    t50 = call printf, 2
L11:
    t51 = j
    j = j + 1
    goto L9
L10:
    param "\n"
    t52 = call printf, 1
L8:
    t53 = i
    i = i + 1
    goto L6
L7:
    return 0
    return
