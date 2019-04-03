.global procdata1
procdata1: save %sp, -64, %sp
           clr %l0       
           clr %l1       
           clr %l2       
           mov 100, %l3  
           clr %l4       
           mov %i1, %o0
           mov 3, %o1
           call .mul
           nop
           mov %o0, %l5

       loop: cmp %l1, %l5
             bge done
             nop
             sll %l1, 2, %l6
             ld [%l6+%i0], %l6
             inc %l1
             sll %l1, 2, %l7
             ld [%l7+%i0], %l7
             add %l6, %l7, %l6
             inc %l1
             sll %l1, 2, %l7
             ld [%l7+%i0], %l7
             add %l6, %l7, %l6
             mov %l6, %o0
             mov 3, %o1
             call .div
             nop
             mov %o0, %l2
             add %l0, %l2, %l0
             low: cmp %l3, %l2
                  ble high
                  nop
                  mov %l2, %l3
             high: cmp %l4, %l2
                   bge cont
                   nop
                   mov %l2, %l4
             cont: inc %l1
                   ba loop
                   nop

       done: mov %l0, %o0
             mov %i1, %o1
             call .div
             nop
             st %l3, [%i2]
             st %l4, [%i3]
             st %o0, [%i4]
             ret
             restore
