# IN4200
High-Performance Computing and Numerical Projects - 2025


Run code with openmp:
gcc-14 -fopenmp test.c -o test  # Use your GCC version
./test #run file


Running on fox cluster:
    - Make account
    - ssh into fox
    - Copy github repo into cluster:
        - scp -r path/to/my/folder ec-username@fox.educloud.no:/fp/projects01/ec54//myFolder (which you have to create)
        - enter password and one time code
    - Use makefile which compiles c files and run command: make
    - Make/run bashscript which includes directions to cluster. includes output file name
        - srun ./w7
    - Run script: sbatch name.sh