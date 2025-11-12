main:
    a = 10
    b = 3
    x = 2.5
    y = 4.0
    t0 = a + b
    sum = t0
    t1 = a - b
    diff = t1
    t2 = a * b
    prod = t2
    t3 = a / b
    quot = t3
    t4 = a % b
    rem = t4
    t5 = x + y
    fsum = t5
    t6 = a + x
    mix = t6
    t7 = y / b
    divf = t7
    param "Integer Operations:\n"
    t8 = call printf, 1
    param "Sum = %d\n"
    param sum
    t9 = call printf, 2
    param "Difference = %d\n"
    param diff
    t10 = call printf, 2
    param "Product = %d\n"
    param prod
    t11 = call printf, 2
    param "Quotient = %d\n"
    param quot
    t12 = call printf, 2
    param "Remainder = %d\n\n"
    param rem
    t13 = call printf, 2
    param "Float Operations:\n"
    t14 = call printf, 1
    param "Float Sum = %.2f\n"
    param fsum
    t15 = call printf, 2
    param "Mixed (a + x) = %.2f\n"
    param mix
    t16 = call printf, 2
    param "Float Division (y / b) = %.2f\n"
    param divf
    t17 = call printf, 2
    return 0
