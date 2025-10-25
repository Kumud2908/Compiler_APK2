main:
    t0 = p.addr
    t0.houseNo = 45
    t1 = p.addr
    t1.zip = 12345
    param "%d %d\n"
    t2 = p.addr
    t3 = t2.houseNo
    param t3
    t4 = p.addr
    t5 = t4.zip
    param t5
    t6 = call printf, 3
    return 0
    return
