add:
     = a param_decl int
     = b param_decl int
    t0 = a + b
    return t0
subtract:
     = a param_decl int
     = b param_decl int
    t1 = a - b
    return t1
multiply:
     = a param_decl int
     = b param_decl int
    t2 = a * b
    return t2
divide:
     = a param_decl int
     = b param_decl int
    t3 = a / b
    return t3
apply_operation:
     = x param_decl int
     = y param_decl int
     = op param_decl int(*)()
    param x
    param y
    t4 = call* op, 2
    return t4
main:
    t5 = &operations
    t6 = 0 * 4
    t7 = t5 + t6
    *t7 = add
    t8 = &operations
    t9 = 1 * 4
    t10 = t8 + t9
    *t10 = subtract
    t11 = &operations
    t12 = 2 * 4
    t13 = t11 + t12
    *t13 = multiply
    t14 = &operations
    t15 = 3 * 4
    t16 = t14 + t15
    *t16 = divide
    a = 20
    b = 4
    param "Operations on %d and %d:\n"
    param a
    param b
    t17 = call printf, 3
    param "Add: %d\n"
    t18 = 0 * 4
    t19 = &operations
    t20 = t19 + t18
    t21 = *t20
    param a
    param b
    t22 = call* t21, 2
    param t22
    t23 = call printf, 2
    param "Subtract: %d\n"
    t24 = 1 * 4
    t25 = &operations
    t26 = t25 + t24
    t27 = *t26
    param a
    param b
    t28 = call* t27, 2
    param t28
    t29 = call printf, 2
    param "Multiply: %d\n"
    t30 = 2 * 4
    t31 = &operations
    t32 = t31 + t30
    t33 = *t32
    param a
    param b
    t34 = call* t33, 2
    param t34
    t35 = call printf, 2
    param "Divide: %d\n"
    t36 = 3 * 4
    t37 = &operations
    t38 = t37 + t36
    t39 = *t38
    param a
    param b
    t40 = call* t39, 2
    param t40
    t41 = call printf, 2
    param "Using apply_operation:\n"
    t42 = call printf, 1
    param "Result: %d\n"
    param 10
    param 5
    param add
    t43 = call apply_operation, 3
    param t43
    t44 = call printf, 2
    param "Result: %d\n"
    param 10
    param 5
    param multiply
    t45 = call apply_operation, 3
    param t45
    t46 = call printf, 2
    return 0
