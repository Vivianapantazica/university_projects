01cSX.

start * R go_right(start_checking)
      # H accept

go_right(S) * R go_right(S)
         # PX,L go_left(S)

go_left(S) * L go_left(S)
        # R S

start_checking 0 H next_group_checking
               1 H substract3
               X R go_to_end

next_group_checking * R b3

b3 * R b2

b2 * R b1

b1 * R start_checking

substract3 * R s3

s3 * R s2

s2 * R s1

s1 0 P1,L s321
   1 P0,L s320

s320 0 P1,L s331
     1 P0,L s330

s321 0 P0,L s331
     1 P1,L s331

s330 0 P0,L s340
     1 P1,L s340

s331 0 P1,L s341
     1 P0,L s340

s340 1 P1,R b3

s341 1 P0,R b3

go_to_end * R go_to_end
          # P#,L shift

shift 0 P#,R put(0)
      1 P#,R put(1)
      X L shiftX
      # P#,R complete_zeroes

shiftX 0 P#,R moveX(0)
       1 P#,R moveX(1)

moveX(c) X R put(c)

complete_zeroes # P0,H stop_condition

put(c) # Pc,L continue

continue * L continue
         # L shift

stop_condition 0 R stop_condition
               1 L go_left(start_checking)
               X P#,L delete

delete 0 P#,L delete
       # H accept
