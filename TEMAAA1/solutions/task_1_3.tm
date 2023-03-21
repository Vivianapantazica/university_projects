01abcfdXRLSH.

start * H go_right

go_right # L add
         * R go_right

add 0 P1,L add1
    1 P0,L carry

carry 0 P0,L carry1
      1 P1,L carry1

carry1 0 P1 accept
       1 P0,L final

add1 0 P1,L accept
     1 P0,L carry1

final 0 P1 accept
      1 P0,L final
      # P1 accept
       