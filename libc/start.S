.section .text
.global _start
_start:
    la      t0, _bss_start
    la      t1, _bss_end
1:
    bge     t0, t1, 1f
    sd      zero, (t0)
    addi    t0, t0, 8
    j       1b
1:
    la      gp, __global_pointer$

    call    main

    li      a7, 0  # exit
    ecall
    