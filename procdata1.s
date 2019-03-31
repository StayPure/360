.global procdata1
procdata1: save %sp, -64, %sp
       clr %l0       ! sum
       clr %l1       ! i
       clr %l2       ! mean1
       clr %l3       ! mean2
       clr %l4       ! mean3
       mov %i1, %o0
       mov 3, %o1
       call .mul
       nop
       mov %o0, %l5  ! numOfExams

       mean1: cmp %l1, %l5
              bge cont1
              nop
              sll %l1, 2, %l6
              ld [%l6+%i0], %l6
              add %l0, %l6, %l0
              add %l1, 3, %l1
              ba mean1
              nop

       cont1: mov %l0, %o0
              mov %i1, %o1
              call .div
              nop
              mov %o0, %l2
              clr %l0
              mov 1, %l1

       mean2: cmp %l1, %l5
              bge cont2
              nop
              sll %l1, 2, %l6
              ld [%l6+%i0], %l6
              add %l0, %l6, %l0
              add %l1, 3, %l1
              ba mean2
              nop

       cont2: mov %l0, %o0
              mov %i1, %o1
              call .div
              nop
              mov %o0, %l3
              clr %l0
	      clr %o0
              mov 2, %l1

       mean3: cmp %l1, %l5
              bge cont3
              nop
              sll %l1, 2, %l6
              ld [%l6+%i0], %l6
              add %l0, %l6, %l0
              add %l1, 3, %l1
              ba mean3
              nop

       cont3: mov %l0, %o0
              mov %i1, %o1
              call .div
              nop
              mov %o0, %l4
              clr %l1
              clr %l6

       momfind: mov %l2, %l0
              mov %l3, %l1
              add %l0, %l1, %l0
              mov %l4, %l1
              add %l0, %l1, %l0
              mov %l0, %o0
              mov 3, %o1
              call .div
              nop
              st %o0, [%i4]

       lowfind: mov %l2, %l6
              cmp %l6, %l3
              ble low2
              nop
              mov %l3, %l6
              low2: cmp %l6, %l4
                     ble llow
                     nop
                     mov %l4, %l6
              llow: st %l6, [%i2]

       highfind: mov %l2, %l6
              cmp %l6, %l3
              bge high2
              nop
              mov %l3, %l6
              high2: cmp %l6, %l4
                     bge lhigh
                     nop
                     mov %l4, %l6
              lhigh: st %l6, [%i3]

	 ret
         restore