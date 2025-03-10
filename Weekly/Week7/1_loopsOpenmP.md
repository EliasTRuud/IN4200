Exercise 1
For each of the following code segments, use OpenMP pragmas to make the
loop parallel, or explain why the code segmenet is not suitable for parallel
execution.


a)
for (i=0; i < (int) sqrt(x); i++) {
    a[i] = 2.3 * x;
    if (i < 10) b[i] = a[i];
}

Sol:
#pragma omp parallel for
for (i=0; i < (int) sqrt(x); i++) {
    a[i] = 2.3 * x;
    if (i < 10) b[i] = a[i];
}

Safe as long as b[i] dont change depending on loop itreation, which it does not.
----------------------------------------------

b)
flag = 0;
for (i = 0; (i<n) & (!flag); i++) {
    a[i] = 2.3 * i;
    if (a[i] < b[i]) flag = 1;
}

Sol:
Many threads will try modify flag, making it not parelellizable. 

----------------------------------------------

c)
for (i = 0; i < n; i++)
    a[i] = foo(i);

Sol:
#pragma omp parallel for
for (i = 0; i < n; i++)
    a[i] = foo(i);
----------------------------------------------

d)
for (i = 0; i < n; i++) {
    a[i] = foo(i);
    if (a[i] < b[i])
        a[i] = b[i];
}

Sol:
Should be safe as we just compare each index with same index.
#pramga omp parallel for
for (i = 0; i < n; i++) {
    a[i] = foo(i);
    if (a[i] < b[i])
        a[i] = b[i];
}
----------------------------------------------

e)
for (i = 0; i < n; i++) {
    a[i] = foo(i);
    if (a[i] < b[i]) break;
}

Sol:
I assume not parrelizable, break not allowed as it impoortant to stop at right time.

----------------------------------------------

f)
dotp = 0;
for (i = 0; i < n; i++)
    dotp += a[i] * b[i];

Sol:
Use reduction with variable on dotp to make sure they dont all write to save memory.
dotp = 0;
#pramga omp parallel for reduction(+:dotp)
for (i = 0; i < n; i++)
    dotp += a[i] * b[i];
----------------------------------------------

g)
for (i = k; i < 2*k; i++)
    a[i] = a[i] + a[i-k];

Sol:
At first i thought not, but it is cause its i-k, meaning the element which is needed is not calculated
by any other thread.
#pragma omp parallel for
for (i = k; i < 2*k; i++)
    a[i] = a[i] + a[i-k];
----------------------------------------------

h)
for (i = k; i < n; i++)
    a[i] = b * a[i-k];

Sol:
Now this one isnt parallelizeable as n might be >> 2k. Meaning some thread might calculate
a[i] before a thread has updated a[i-k].

----------------------------------------------