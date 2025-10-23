main:
    a = 10
    s = "Hello"
    param "a = %d\n"
    param a
    t0 = call printf, 2
    param "Point: (%d, %d)\n"
    param 
    param 
    t1 = call printf, 3
    param "String: %s\n"
    param s
    t2 = call printf, 2
    return 0
    return
