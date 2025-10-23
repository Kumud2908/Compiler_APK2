main:
    i = 0
    j = 0
    sum = 0
    limit = 5
L0:
    j = 0
L2:
    t0 = i * j
    t1 = sum + t0
    sum = t1
    t2 = i + j
    t3 = t2 % 2
    t4 = t3 == 0
    ifFalse t4 goto L4
    t5 = sum + 1
    sum = t5
    goto L5
L4:
    t6 = sum - 1
    sum = t6
L5:
    t7 = j
    j = j + 1
    t8 = limit - i
    t9 = j < t8
    if t9 goto L2
L3:
    t10 = sum % 10
    t11 = t10 == 0
    ifFalse t11 goto L6
    t12 = i + 2
    i = t12
    goto L7
L6:
    t13 = i
    i = i + 1
L7:
    param "i=%d, sum=%d\n"
    param i
    param sum
    t14 = call printf, 3
    t15 = i < limit
    if t15 goto L0
L1:
    return 0
    return
