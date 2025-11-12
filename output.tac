main:
    t0 = &matrix1
    *t0 = 1
    t1 = t0 + 4
    *t1 = 2
    t2 = t0 + 8
    *t2 = 3
    t3 = t0 + 12
    *t3 = 4
    t4 = t0 + 16
    *t4 = 5
    t5 = t0 + 20
    *t5 = 6
    t6 = t0 + 24
    *t6 = 7
    t7 = t0 + 28
    *t7 = 8
    t8 = t0 + 32
    *t8 = 9
    t9 = &matrix2
    *t9 = 9
    t10 = t9 + 4
    *t10 = 8
    t11 = t9 + 8
    *t11 = 7
    t12 = t9 + 12
    *t12 = 6
    t13 = t9 + 16
    *t13 = 5
    t14 = t9 + 20
    *t14 = 4
    t15 = t9 + 24
    *t15 = 3
    t16 = t9 + 28
    *t16 = 2
    t17 = t9 + 32
    *t17 = 1
    param "Matrix 1:\n"
    t18 = call printf, 1
    i = 0
L0:
    t19 = i < 3
    ifFalse t19 goto L1
    j = 0
L3:
    t20 = j < 3
    ifFalse t20 goto L4
    param "%d "
    t21 = i * 3
    t22 = t21 + j
    t23 = t22 * 4
    t24 = &matrix1
    t25 = t24 + t23
    t26 = *t25
    param t26
    t27 = call printf, 2
L5:
    t28 = j
    j = j + 1
    goto L3
L4:
    param "\n"
    t29 = call printf, 1
L2:
    t30 = i
    i = i + 1
    goto L0
L1:
    param "\nMatrix 2:\n"
    t31 = call printf, 1
    i = 0
L6:
    t32 = i < 3
    ifFalse t32 goto L7
    j = 0
L9:
    t33 = j < 3
    ifFalse t33 goto L10
    param "%d "
    t34 = i * 3
    t35 = t34 + j
    t36 = t35 * 4
    t37 = &matrix2
    t38 = t37 + t36
    t39 = *t38
    param t39
    t40 = call printf, 2
L11:
    t41 = j
    j = j + 1
    goto L9
L10:
    param "\n"
    t42 = call printf, 1
L8:
    t43 = i
    i = i + 1
    goto L6
L7:
    i = 0
L12:
    t44 = i < 3
    ifFalse t44 goto L13
    j = 0
L15:
    t45 = j < 3
    ifFalse t45 goto L16
    t46 = i * 3
    t47 = t46 + j
    t48 = t47 * 4
    t49 = &matrix1
    t50 = t49 + t48
    t51 = *t50
    t52 = j * 3
    t53 = t52 + i
    t54 = t53 * 4
    t55 = &transposed
    t56 = t55 + t54
    *t56 = t51
L17:
    t57 = j
    j = j + 1
    goto L15
L16:
L14:
    t58 = i
    i = i + 1
    goto L12
L13:
    param "\nTransposed Matrix 1:\n"
    t59 = call printf, 1
    i = 0
L18:
    t60 = i < 3
    ifFalse t60 goto L19
    j = 0
L21:
    t61 = j < 3
    ifFalse t61 goto L22
    param "%d "
    t62 = i * 3
    t63 = t62 + j
    t64 = t63 * 4
    t65 = &transposed
    t66 = t65 + t64
    t67 = *t66
    param t67
    t68 = call printf, 2
L23:
    t69 = j
    j = j + 1
    goto L21
L22:
    param "\n"
    t70 = call printf, 1
L20:
    t71 = i
    i = i + 1
    goto L18
L19:
    i = 0
L24:
    t72 = i < 3
    ifFalse t72 goto L25
    j = 0
L27:
    t73 = j < 3
    ifFalse t73 goto L28
    t74 = i * 3
    t75 = t74 + j
    t76 = t75 * 4
    t77 = &product
    t78 = t77 + t76
    *t78 = 0
    k = 0
L30:
    t79 = k < 3
    ifFalse t79 goto L31
    t80 = i * 3
    t81 = t80 + k
    t82 = t81 * 4
    t83 = &matrix1
    t84 = t83 + t82
    t85 = *t84
    t86 = k * 3
    t87 = t86 + j
    t88 = t87 * 4
    t89 = &matrix2
    t90 = t89 + t88
    t91 = *t90
    t92 = t85 * t91
    t93 = i * 3
    t94 = t93 + j
    t95 = t94 * 4
    t96 = &product
    t97 = t96 + t95
    t98 = *t97
    t99 = t98 + t92
    *t97 = t99
L32:
    t100 = k
    k = k + 1
    goto L30
L31:
L29:
    t101 = j
    j = j + 1
    goto L27
L28:
L26:
    t102 = i
    i = i + 1
    goto L24
L25:
    param "\nMatrix 1 * Matrix 2:\n"
    t103 = call printf, 1
    i = 0
L33:
    t104 = i < 3
    ifFalse t104 goto L34
    j = 0
L36:
    t105 = j < 3
    ifFalse t105 goto L37
    param "%d "
    t106 = i * 3
    t107 = t106 + j
    t108 = t107 * 4
    t109 = &product
    t110 = t109 + t108
    t111 = *t110
    param t111
    t112 = call printf, 2
L38:
    t113 = j
    j = j + 1
    goto L36
L37:
    param "\n"
    t114 = call printf, 1
L35:
    t115 = i
    i = i + 1
    goto L33
L34:
    return 0
