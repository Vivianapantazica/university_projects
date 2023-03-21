01cyRLSX.

start * L mark
      # L go_left(#)

mark # Py,R go_right

go_right X L cpy
         # L cpy   
         y R verify
         * R go_right

verify X R f(y, q(X))
       * R go_right

fr(y, S) y PX,H S
         # L accept
         * R fr(y, S)

f(y, S) * H rewind(fr(y, S))

rewind(S) # R S 
          * L rewind(S)

q(X) # L ql(X)
     * R q(X)

ql(X) X H delete_final
      # R accept
      * L ql(X)

delete_final * P# rewind2(mark2)
            
cpy 0 PX go_left(0)
    1 PX go_left(1)
        
go_left(c) # H put(c)
           * L go_left(c)

put(c) # Pc go_right

rewind2(S) # L S 
           * R rewind2(S)

mark2 # L mark2
      X P#,L go_start(putX)
      * H accept

go_start(S) * L go_start(S)
            # R S

go_end(S) * R go_end(S)
          # R S

putX * L putX
     # PX go_end(mark2)
