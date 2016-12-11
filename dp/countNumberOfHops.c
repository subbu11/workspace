/*
Frog steps either 1, 2 or 3 steps to go to top. In how many ways it reaches the top?

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is N. Where is the number of steps it has to hop.

Output:

Print the number of ways.

Constraints:

1 ≤ T ≤ 50
1 ≤ N ≤ 50

Example:

Input:
2
1
5

Output:
1
13
*/

#include <stdio.h>

int countWays(int top, int maxJump)
{
    int i, j;

    /*
    http://mathworld.wolfram.com/FibonacciNumber.html
    fibbonaci series : 1, 1, 2, 3, 5, ...
    f(1) = 1
    f(2) = 1
    */
    /* ways(1) = fib(2) = 1
     * ways(2) = fib(3) = 3
     * ways(3) = fib(4) = 5
     */
    int res[top + 1]; /* here we are taking (top+1)
    because of the matching fibbonaci series */

    res[0] = 1; /*i.e. fib(1), ways to reach 1st floor*/
    res[1] = 1; /*i.e. fib(2), ways to reach 2nd floor*/

    for(i = 2; i <= top; i++)
    {
        res[i] = 0;
        for(j = 1; j <= i && j <= maxJump; j++)
        {
            /* if maxJump = 2
             * total number of ways to reach top=4 
             *  = total number of ways to reach top=3
             *     + total number of ways to reach top=2 
             *  */

             /* if maxJump = 3
             * total number of ways to reach top=4 
             *  = total number of ways to reach top=3
             *     + total number of ways to reach top=2 
             *     + total number of ways to reach top=1 
             *  */
            res[i] = res[i] + res[i-j]; 
        }
    }

    return res[top]; /*ways to reach (top+1)th floor*/
}

int main()
{
    int numStairs = 4, maxJump = 3;
    printf("Nuber of ways = %d", countWays(numStairs, maxJump));
    return 0;
}
