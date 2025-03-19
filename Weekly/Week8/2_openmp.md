If the following code snippet is executed by 4 OpenMP threads, what will be written as output?


int main() {
    int total_sum = 0;
    int i;

    #pragma omp parallel default(shared) reduction(+:total_sum)
    {
        int my_id = omp_get_thread_num();
        int my_sum = 0;

        #pragma omp for schedule(static,10)
        for (i=1; i<=100; i++) {
            my_sum += i;  // Accumulates inside the loop
        }

        printf("From thread No.%d: my_sum=%d\n", my_id, my_sum);
        total_sum += my_sum;  // Adds local sum to total sum
    }

    printf("Total sum=%d\n", total_sum);
    return 0;
}

4 threads adding up sections of 10:
Calculate using formula (B-A+1)/2*(A+B)

id          Sections assigned       Sums:
Thread 0	1-10,  41-50, 81-90: 	55 + 455 + 855 = 1365
Thread 1	11-20, 51-60, 91-100: 	155 + 555 + 955 = 1665
Thread 2	21-30, 61-70:	        255 + 655 = 910
Thread 3	31-40, 71-80:	        355 + 755 = 1110

Output:
From thread No.2: my_sum=910
From thread No.3: my_sum=1110
From thread No.0: my_sum=1365
From thread No.1: my_sum=1665
Total sum=5050