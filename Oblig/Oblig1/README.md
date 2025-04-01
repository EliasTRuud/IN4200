## Oblig 1 - Computing PageRank
### IN3200/IN4200 Obligatory assignment 1, Spring 2025¨

Im sure there's smarter ways to compile the files with makefile, but i just manually compiled them all by typing them out in terminal. 

Instead of using command line arguments i just added the variables top of main.c and main_omp.c where i can change textfile, and the N is decided by the choice of the string from known 3 files. Ideally i wanna change this to automatically read in N and use cmd line arguments. For now i found this easier to run and compile. So just compile and run the main and main_omp, which respectively runs with the txt files (simple.txt for dense matrix and notredame.txt for CRS) and omp also uses notredame.txt