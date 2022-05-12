
# Used in ?

The construction of both top-down and bottom-up parsers is aided by two
functions, FIRST and FOLLOW, associated with a grammar G. During topdown parsing, FIRST and FOLLOW allow us to choose which production to
apply, based on the next input symbol. During panic-mode error recovery, sets
of tokens produced by FOLLOW can be used as synchronizing tokens.




# Algorithm

1. If x is a terminal, then FIRST(x) = { ‘x’ }
2. If x `->` Є, is a production rule, then add Є to FIRST(x). 
3. If X `->` Y1 Y2 Y3….Yn is a production,
   * FIRST(X) = FIRST(Y1)
   * If FIRST(Y1) contains Є then FIRST(X) = { FIRST(Y1) – Є } U { FIRST(Y2) }
   * If FIRST (Yi) contains Є for all i = 1 to n, then add Є to FIRST(X).

# Rules

Non-Terminal : each letter in it must be upper case.

Terminal : each letter in it must be upper case.

Epsilon : $


### Example ###

EXPR `->` EXPRS + id  
EXPR `->` $  
EXPRS `->` id

**Note** : Between Terminal or Non-Terminal only 1 space and only one space between Non-Terminal and arrow ` -> `

