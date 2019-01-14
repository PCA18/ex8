#!/usr/bin/env bash
# Partition to use
#SBATCH --partition=bench 
#
# Number of nodes
#SBATCH --nodes 2
# #SBATCH --tasks-per-node=2
#
# Runtime of this jobs is less then 1 hour.
#SBATCH --time=1:00:00

module load mpi/openmpi-x86_64

echo "2 Knoten 1 Rank"
mpirun -n 2 -N 1 ./lat.exe
echo "1 Knoten 2 Rank"
mpirun -n 2 -N 2 ./lat.exe

