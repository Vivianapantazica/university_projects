01abcefjhXY.

start * H go_right

go_right # L a(b(c, a(final, f)), a(a(final, f), b(f, f)))
         * R go_right

a(X, Y) 0 P1,L X
        1 P0,L Y

b(X, Y) 0 P0,L X
        1 P1,L Y

c 1 P0 f
  0 L final

final 1 P0 f
      0 P1,L final
      # P1,H f

rewind(S) # R S 
          * L rewind(S)

fr 1 H accept
   # L accept
   0 P#,R fr

f * H rewind(fr)
