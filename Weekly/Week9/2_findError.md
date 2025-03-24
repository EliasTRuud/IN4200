

There is one (or several) error(s) in the following OpenMP code. Please
correct the error(s). Is there anything that can be further improved?


int i, N = 100000;
double u[N], v[N];

for (i = 0; i < N; i++) {
    u[i] = 0.001 * (i - N / 2);
    v[i] = 0.0;
}

#pragma omp parallel default(shared)
{
    int time_step;
    double *tmp;

    for (time_step = 0; time_step < 1000; time_step++) {
        #pragma omp for nowait
        for (i = 1; i < N - 1; i++)
            v[i] = u[i - 1] - 2 * u[i] + u[i + 1];

        tmp = v;
        v = u;
        u = tmp;
    }
}


### Errors OR improvements
1. We can parraelize the initial for loop which sets up u and v values.
2. THe pointer swappings has to be done only by one thread. Dont want all thread trying to change pointer.
3. The i variable is created outside for loop OMP, so all the thread will update i. To change this we can make i private.