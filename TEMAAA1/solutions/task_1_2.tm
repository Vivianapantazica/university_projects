01abcfdXRLSH.

start * H go_right

go_right # Pc,R put1
         * R go_right

put1 # P1,R put0

put0 # P0,R put11

put11 # P1,L rewind(fr(c, verify(c)))

rewind(S) # R S 
          * L rewind(S)

fr(c, S) c R S
         * R fr(c, S)

ql(X, S) X H S
         * L ql(X, S)
         # R stop(1)

q(X, S) # L ql(X, S)
        * R q(X, S)

verify(d) * PX,R verify(d)
          # L delete

delete X P#,L rewind(mark)
       c H stop(0)
       * H q(X, delete)
      
mark * P#,R delete
     c H stop(1)

stop(d) # Pd accept
        * P#,R stop(d)
 