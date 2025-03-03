
There are n equal-sized independent tasks and p equal workers. Suppose n
is not divisible by p. How to divide the n tasks among the p workers in a fair
way?


The following work decomposition will guarantee that the maximum difference between “heavy-load” and “light-load” tasks is at most 1.
Processor core number k computes y[start_k],
y[start_k+1], ... y[stop_k-1]
where start_k=k*N/P and stop_k=(k+1)*N/P

n/p => 4 tasks per worker. Rest is 2 is spread out.