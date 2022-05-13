# Used in ?

The construction of both top-down and bottom-up parsers is aided by two
functions, FIRST and FOLLOW, associated with a grammar G. During topdown parsing, FIRST and FOLLOW allow us to choose which production to
apply, based on the next input symbol. During panic-mode error recovery, sets
of tokens produced by FOLLOW can be used as synchronizing tokens.

# Algorithm

1. FOLLOW(S) = { $ } // where S is the starting Non-Terminal

2. If A `->` pBq is a production, where p, B and q are any grammar symbols,
   then everything in FIRST(q) except Є is in FOLLOW(B).

3. If A `->` pB is a production, then everything in FOLLOW(A) is in FOLLOW(B).

4. If A `->` pBq is a production and FIRST(q) contains Є,
   then FOLLOW(B) contains { FIRST(q) – Є } U FOLLOW(A)

# Rules

Non-Terminal : each letter in it must be upper case.

Terminal : each letter in it must be upper case.

Epsilon : $   
-| : end of file 

### Example

EXPR `->` EXPRS + id  
EXPR `->` $  
EXPRS `->` id

**Note** : Between Terminal or Non-Terminal only 1 space and only one space between Non-Terminal and arrow `->`
