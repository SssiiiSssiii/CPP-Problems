# Algorithm

1. If x is a terminal, then FIRST(x) = { ‘x’ }
2. If x-> Є, is a production rule, then add Є to FIRST(x). 
3. If X->Y1 Y2 Y3….Yn is a production,

⋅⋅* FIRST(X) = FIRST(Y1)
⋅⋅* If FIRST(Y1) contains Є then FIRST(X) = { FIRST(Y1) – Є } U { FIRST(Y2) }
⋅⋅* If FIRST (Yi) contains Є for all i = 1 to n, then add Є to FIRST(X).
