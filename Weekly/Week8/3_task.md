Exercise 3: Sorting by odd-even transposition
Given a list of numbers: a1, a2, . . . , an, the following odd-even transposition 
algorithm can be used to sort the list into an increasing order:

1. procedure ODD-EVEN(n)
2. begin
3.     for i := 1 to n do
4.         begin
5.             if i is odd then
6.                 for j := 0 to (n/2) − 1 do
7.                     compare-exchange(a[2j+1], a[2j+2]);
8.             if i is even then
9.                 for j := 1 to (n/2) − 1 do
10.                    compare-exchange(a[2j], a[2j+1]);
11.        end for
12. end ODD-EVEN


a. Serial implementation
Please program a serial function void serial odd even(int n, float *a)
that implements the odd-even transposition algorithm. Write a simple program to test the correctness of this function.
