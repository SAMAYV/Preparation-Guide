1)Ehab and the Expected XOR Problem
https://codeforces.com/contest/1174/problem/D
When we have to find some subsegment with some property,
construct an prefix array with that property and Then
construct the original array.
A subsegment can be represented by prefix arrays!!!

2)Pavel and Triangles
https://codeforces.com/contest/1119/problem/E
First make tuples with not having all the elements same,
then make tuples with all elements same.

3)Beautiful Array
https://codeforces.com/contest/1155/problem/D
Analyse different states of DP
0:just add before multiply any element
1:add and multiply
2:add after all being multiplieds

4)Count Pairs
https://codeforces.com/contest/1189/problem/E
if n mod(p)!=0
then we can multiply the given eqn by n
all elements of array are different hence 0<abs(a[i]-a[j])<p

5)Crazy Diamond
https://codeforces.com/contest/1148/problem/C
To swap two elements we can swap apt extra elements
making the array unaltered.

6)Two Teams
https://codeforces.com/contest/1154/problem/E
auto it=next(s.find());
is same as
auto it=s.find();
it++;
queues and sets make a deadly combo

7)Tokitsukaze, CSL and Stone Game
https://codeforces.com/contest/1191/problem/D
Make proper cases for initial conditions:
USE PEN AND PAPER

8)Tennis Championship
https://codeforces.com/contest/736/problem/A
Sometimes solve the converse of the problem.
Here we have solved for numbers of wins.

9)Vacation
https://atcoder.jp/contests/dp/tasks/dp_c
Analyse dp step by step
dp[n+1][3]

10)Dima and a Bad XOR
https://codeforces.com/contest/1151/problem/B
Assume an ans then check whether its true or NOT
if not find some way to find it.

11)Valid BFS?
https://codeforces.com/contest/1037/problem/D
sort a given array in the order of input of elements;
bool comp(int x, int y)
{
    return a[x] < a[y];
}

12)Polygons
https://codeforces.com/contest/166/problem/B
Make convex hull of all the points ans perturb the conditions.

13)Ceasers Legions
https://codeforces.com/problemset/problem/118/D
Make 3 states one for no of horsemen one for riders
and current char 
dp[n1+1][n2+1][2]

14)Flowers 
https://codeforces.com/problemset/problem/474/D
Dont forget to consider subtraction while using mod 




