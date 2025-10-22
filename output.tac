main:
    x = 4
    j = 0
    k = 0
L0:
    t0 = k < 10
    ifFalse t0 goto L1
L2:
    t1 = j < 5
    ifFalse t1 goto L3
    goto L2
L3:
    t2 = k
    k = k + 1
    goto L0
L1:
    return 0
    return
