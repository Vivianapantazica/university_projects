01abcdmXxys.

start * L mark
      # L accept

mark # Ps,R go_to_end

go_to_end * R go_to_end
          # L digit1
          s R go_to_end

digit1 0 Px,L digit2
       1 Py,L digit2
       s R transform
       x L digit1
       y L digit1
       # H accept

digit2 0 Px,L digit3
       1 Py,L digit3
       * L digit2
       s R transform
       # H accept

digit3 0 Px,R go_before_s
       1 Py,R go_before_s
       s R transform
       # H accept

go_before_s * L go_before_s
            s L put_zeroes1

put_zeroes1 # P0,R put_zeroes2
           * L put_zeroes1

put_zeroes2 # P0,R put_zeroes3
           * L put_zeroes2

put_zeroes3 # P0,R put_zeroes4
           * L put_zeroes3

put_zeroes4 # P0,R go_to_end
           * L put_zeroes4

transform * R transform
          # L convert

convert x P0 convert
        y P1 convert
        * L convert
        s R shift

shift 0 PX,L put(0)
      1 PX,L put(1)
      X R final_test

final_test * H shift
           # L delete

put(c) 0 Pc,L put_next(0)
       1 Pc,L put_next(1)
       * L put(c)
       # R rewind_to_s_l(verify)

put_next(c) 0 Pc,L put(0)
            1 Pc,L put(1)
            * L put_next(c)
            # R rewind_to_s_l(verify)

rewind_to_s_r(S) s R S
                 * R rewind_to_s_r(S)

rewind_to_s_l(S) s L S
                 * R rewind_to_s_l(S)

verify 0 L verify1
       1 L verify2
       # R rewind_to_s_r(shift)

verify1 0 L verify3
        1 L verify4
      
verify2 0 L verify4
        1 L verify4
       
verify3 0 L verify7
        1 L verify7
     
verify4 0 L verify7
        1 L verify8
      
verify7 0 L verify
        1 R step_back
        
verify8 0 R step_back
        1 R step_back
        
step_back * R step_back1

step_back1 * R step_back2

step_back2 * H add3

add3 0 P1,L b
     1 P0,L c

b 0 P1,L de
  1 P0,L e

c 0 P0,L e
  1 P1,L e

de 0 P0,L final
  1 P1,L final

e 0 P1,L final
  1 P0,L final

final * P1,L verify
    
delete * P#,L delete
       0 L delete
       1 L delete
       # R nxt

nxt 1 R nxt1
    0 R parcurgere_grupa(nxt)
    # L last_check

nxt1 0 R nxt2
     1 R nxt3

nxt2 0 R nxt4
     1 R nxt5

nxt3 0 R nxt6
     * H accept

nxt4 0 P1,L ref0
     1 P0,L ref1

nxt5 0 P1,L ref1
     1 P0,L ref6

nxt6 0 P1,L ref6
     * H accept

ref0 * P0,L ref2

ref1 * P1,L ref4

ref2 * P1,L ref3

ref3 * P0,R parcurgere_grupa(nxt)

ref4 * P1,L ref5

ref5 * P0,R parcurgere_grupa(nxt)

ref6 * P0,L ref7

ref7 * P0,L ref8

ref8 * P1,R parcurgere_grupa(nxt)

parcurgere_grupa(S) * R pas1(S)
                  
pas1(S) * R pas2(S)

pas2(S) * R S

last_check * L last_check
           # R cont0

cont0 0 R cont
      * H accept

cont 1 R cont1
     * H accept

cont1 1 R cont2
     * H accept

cont2 1 R cont3
      * H accept

cont3 * L cont3
      # P1,L put_carry

put_carry # P0,L put00

put00 # P0,L put000

put000 # P0 accept
