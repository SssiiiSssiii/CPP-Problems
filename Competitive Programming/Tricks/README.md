## Number of Digits for `n` number
1 + floor (log10(n))

## Number of Bits for `n` number
1 + floor (log2(n))

## The Decimal representation for `n`  which consists only of `1's`
 ( 1 << `1's` ) -1 = pow (2 , `1's`)-1  
 https://codeforces.com/group/T3p02rhrmb/contest/325687/problem/X  
 
 ## The sum of Numbers from `1` to `n`
 ( n * ( n + 1 ) ) / 2  
 https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/G
 
 https://codeforces.com/group/XGW5NIn8kq/contest/391344/problem/D

## GCD using built-in function
__gcd ( `x` ,  `y` )   
https://codeforces.com/group/T3p02rhrmb/contest/325687/problem/L
## LCM using GCD
``(n / GCD) * m``

## Fibonacci Number in o(1)
![Alt text](/images/Binet'sFormula.png)    
https://codeforces.com/group/T3p02rhrmb/contest/325687/problem/Y   
more information   
https://artofproblemsolving.com/wiki/index.php/Binet%27s_Formula

## Max element in array
 int max = *max_element ( `arr` , `arr+n` )  , Where `arr` means the first element and `arr+n` the last element  
 https://codeforces.com/group/T3p02rhrmb/contest/325687/problem/E  
 
 ## Conditional Operator
 ```c
 if ( x == 5 )  
      cout << "yes";  
  else  
      cout << "no"; 
 ```
  you can use &rarr; cout << ( x == 5  `?` "yes" `:` "no" );   
  
 ## Sum of even numbers from 1 to n
 ``n*(n+1)``
 
  ## Sum of odd numbers from 1 to n
 ``ceil(n / 2) * ceil(n / 2) ``
 
 ## Sum of range from n to m or any Arithmetic progression
 ``((n + m) * (m - n + 1)) / 2``
 
 ## Numbers of odd numbers from low to high 
 if low is odd &rarr; ((high - low) / 2) + 1                 
 else increment low then  ((high - low) / 2) + 1                             
 https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/solutions/2957338/count-odd-numbers-in-an-interval-range/
  

