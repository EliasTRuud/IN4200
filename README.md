# IN4200
High-Performance Computing and Numerical Projects - 2025

Run code, compile and run:
gcc -o file file.c

Run code with openmp:
gcc-13 -fopenmp test.c -o test  # Use your GCC version
./test #run file

Run code with mpi:
mpicc hello_world.c
mpirun -np 4 ./a.out


Running on fox cluster:
    - Make account
    - ssh into fox
        - ssh ec-eliastr@fox.educloud.no
        - enter onetimecode + password123
    - Copy github repo into cluster:
        - scp -r path/to/my/folder ec-username@fox.educloud.no:/fp/projects01/ec54//myFolder (which you have to create)
        - enter password and one time code
    - Use makefile which compiles c files and run command
        - make
    - Make/run bashscript which includes directions to cluster. includes output file name
        - srun ./w7
    - Run script: sbatch <name>.sh , example 
        - sbatch week7.sh

    - Once batch is submitted theres some commands to monitor/navigate:
        -Out
    
    - Check output of file in directory:


Commands for batch:
# Useful SLURM commands for job management:
# squeue -u <username>          # Check the status of your submitted jobs
# sinfo                         # View the status of all available queues
# squeue --start -u <username>  # Check estimated start time of pending jobs
# sbatch week7.sh               # Submit this script to SLURM