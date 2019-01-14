#!/usr/bin/env bash
#SBATCH --partition=bench
#SBATCH --nodes 2
module load mpi/openmpi-x86_64

echo "2 Knoten 1 Rank"
mpirun -n 2 -N 1 ./lat.exe
echo "1 Knoten 2 Rank"
mpirun -n 2 -N 2 ./lat.exe

