area:
     = r param_decl struct Rectangle
    t0 = &r
    t1 = t0 + 8
    t2 = *t1
    t3 = &r
    t4 = *t3
    t5 = t2 - t4
    width = t5
    t6 = &r
    t7 = t6 + 8
    t8 = *t7
    t9 = &r
    t10 = *t9
    t11 = t8 - t10
    height = t11
    t12 = width * height
    return t12
main:
    t13 = &p1
    *t13 = 0
    t14 = &p1
    t15 = t14 + 4
    *t15 = 0
    t16 = &p2
    *t16 = 10
    t17 = &p2
    t18 = t17 + 4
    *t18 = 5
    t19 = p1[0]
    t20 = &rect
    *t20 = t19
    t21 = &rect
    t22 = t21 + 8
    *t22 = p2
    param "Rectangle area: %d\n"
    t24 = &rect
    t25 = t24 + 0
    t25 = *t23
    param t23
    t27 = &rect
    t28 = t27 + 4
    t28 = *t26
    param t26
    t30 = &rect
    t31 = t30 + 8
    t31 = *t29
    param t29
    t33 = &rect
    t34 = t33 + 12
    t34 = *t32
    param t32
    t35 = call area, 4
    param t35
    t36 = call printf, 2
    t37 = &p1
    ptr = t37
    *ptr = 5
    t38 = ptr + 4
    *t38 = 3
    param "Point: (%d, %d)\n"
    t39 = *ptr
    param t39
    t40 = ptr + 4
    t41 = *t40
    param t41
    t42 = call printf, 3
    return 0
