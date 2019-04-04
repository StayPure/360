/* Design a module that takes in an array of test scores, number of 
   students and then returns the lowest, highest, and mean of means 
   using SPARC assembly language.
   Set L0 as the total sum of all the means, set L1 as the counter 
   for the main loop, set L2 as the current mean, set L3 to the lowest
   mean starting at 100 so its set to the first mean, set L4 to the 
   highest mean, and set L5 to the number of students * 3 for easy
   comparisons. The loop then starts by comparing i to nstudents * 3
   if its greater than or equal to stop the loop otherwise continue
   we add the ith students score in the array incrementing i for each
   score and loading them so they can be added, then divide it by 3 to 
   get that students mean. The mean is then add to the running sum and 
   compared to the lowest mean and the highest mean to see if it is the 
   lowest or highest thus far then i is incremented once more and the loop
   is continued. When it is over the sum and number of students is divided
   to get the mean of means lastly the lowest mean, highest mean, and mean 
   of means are then stored in there respected addresses.
*/


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
