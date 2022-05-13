# Used in ?

The construction of both top-down and bottom-up parsers.   

# Algorithm

Step 1:  First check for left recursion in the grammar, if there is left recursion in the grammar remove that and go to step 2.   

Step 2: Calculate First() and Follow() for all non-terminals.    

First() : If there is a variable, and from that variable, if we try to drive all the strings then the beginning Terminal Symbol is called the First.    
Follow() : What is the Terminal Symbol which follows a variable in the process of derivation.    

Step 3: For each production A –> α. (A tends to alpha)

Find First(α) and for each terminal in First(α), make entry A –> α in the table.    
If First(α) contains ε (epsilon) as terminal than, find the Follow(A) and for each terminal in Follow(A), make entry A –> α in the table.    
If the First(α) contains ε and Follow(A) contains $ as terminal, then make entry A –> α in the table for the $.    

To construct the parsing table, we have two functions:     
 
In the table, rows will contain the Non-Terminals and the column will contain the Terminal Symbols. All the Null Productions of the Grammars will go under the Follow elements and the remaining productions will lie under the elements of the First set.     

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
