#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idx;
    double score;
} Page;

int comparePages(const void *a, const void *b) {
    // Initally i tried just to manually go through a list of scores then compare
    // 1 and 1. But using chatgpt it reccomended a struct and using that to compare.
    // Which seems much nicer and more efficient using qsort.
    Page *p1 = (Page *)a;
    Page *p2 = (Page *)b;
    if (p1->score < p2->score)
        return 1;  // p2 comes before p1
    else if (p1->score > p2->score)
        return -1; // p1 comes before p2
    else
        return 0;
}
void top_n_webpages (int N, double *scores, int n) {
    // allocate an array to hold index and score for each webpage
    Page *pages = malloc(N * sizeof(Page));
    for (int i = 0; i < N; i++) {
        pages[i].idx = i;
        pages[i].score = scores[i];
    }
    // sort pages in descending order by score using qsort
    qsort(pages, N, sizeof(Page), comparePages);
    
    // print top n webpags
    printf("Top %d webpages:\n", n);
    for (int i = 0; i < n && i < N; i++) {
        printf("Webpage %d: %.4f\n", pages[i].idx, pages[i].score);
    }
    
    free(pages);
}
