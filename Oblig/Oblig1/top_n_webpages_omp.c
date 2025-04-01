#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idx;
    double score;
} Page;

int comparePages_(const void *a, const void *b) {
    Page *p1 = (Page *)a;
    Page *p2 = (Page *)b;
    if (p1->score < p2->score)
        return 1;  // p2 comes before p1
    else if (p1->score > p2->score)
        return -1; // p1 comes before p2
    else
        return 0;
}
void top_n_webpages_omp(int N, double *scores, int n) {
    // allocate an array to hold index and score for each webpage
    Page *pages = malloc(N * sizeof(Page));
    #pragma omp parallel for // just added one omp for
    for (int i = 0; i < N; i++) {
        pages[i].idx = i;
        pages[i].score = scores[i];
    }
    // sort pages in descending order by score using qsort
    qsort(pages, N, sizeof(Page), comparePages_);
    
    // print top n webpags
    printf("Top %d webpages:\n", n);
    for (int i = 0; i < n && i < N; i++) {
        printf("Page id: %d: %.4f\n", pages[i].idx, pages[i].score);
    }
    
    free(pages);
}
