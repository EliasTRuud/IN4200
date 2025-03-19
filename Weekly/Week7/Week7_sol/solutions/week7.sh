#!/bin/bash

# SLURM job script for submitting a simple job

#SBATCH --account=ec54                # Specify the project/account to charge for the job
#SBATCH --job-name=simple              # Name of the job (change as needed)
#SBATCH --nodes=1                      # Number of nodes requested
#SBATCH --ntasks-per-node=1            # Number of tasks per node (single task in this case)
#SBATCH --cpus-per-task=8              # Number of CPU cores per task
#SBATCH --mem-per-cpu=1G               # Memory allocated per CPU core (1GB per core)
#SBATCH --time=0-00:01:00              # Maximum runtime (D-HH:MM:SS), here set to 1 minute
#SBATCH --qos=devel                    # Quality of Service (QOS) for development/testing jobs
#SBATCH --output=ex2.out               # Output file for job logs (change name for different exercises)

# Set the number of OpenMP threads 
export OMP_NUM_THREADS=8

# Exit immediately if a command exits with a non-zero status
set -o errexit  
# Treat unset variables as an error to prevent unexpected behavior
set -o nounset  

# Purge all currently loaded modules to ensure a clean environment
module --quiet purge  

# Execute the compiled program (update filename as needed for different exercises)
srun ./w7_e2_scheduling.o  

# Useful SLURM commands for job management:
# squeue -u <username>          # Check the status of your submitted jobs
# sinfo                         # View the status of all available queues
# squeue --start -u <username>  # Check estimated start time of pending jobs
# sbatch week7.sh               # Submit this script to SLURM
