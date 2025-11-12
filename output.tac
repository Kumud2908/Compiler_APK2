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
main:
    x = 10
    y = 5
    operation = add
    param "Addition: %d + %d = %d\n"
    param x
    param y
    param x
    param y
    t3 = call* operation, 2
    param t3
    t4 = call printf, 4
    operation = subtract
    param "Subtraction: %d - %d = %d\n"
    param x
    param y
    param x
    param y
    t5 = call* operation, 2
    param t5
    t6 = call printf, 4
    operation = multiply
    param "Multiplication: %d * %d = %d\n"
    param x
    param y
    param x
    param y
    t7 = call* operation, 2
    param t7
    t8 = call printf, 4
    return 0
