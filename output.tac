add:
     = a param_decl int
     = b param_decl int
    t0 = a + b
    return t0
mul:
     = a param_decl int
     = b param_decl int
    t1 = a * b
    return t1
main:
    param 2
    param 3
    t2 = call mul, 2
    param t2
    param 5
    t3 = call add, 2
    result = t3
    param "%d\n"
    param result
    t4 = call printf, 2
    return 0
