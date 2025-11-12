main:
    i = 0
    a = 0
    i = 0
L0:
    a = a + 1
    t0 = a
    t1 = 5 + t0
    t2 = i < t1
    ifFalse t2 goto L1
    param "%d %d\n"
    param i
    param a
    t3 = call printf, 3
L2:
    t4 = i + a
    i = t4
    goto L0
L1:
