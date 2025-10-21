factorial:
    t0 = n <= 1
    ifFalse t0 goto L0
    return 1
L0:
    t1 = n - 1
    param t1
    t2 = call factorial, 1
    t3 = * n
    return t3
    return
main:
    param 1
    t4 = call printf, 1
    return 0
    return
