Suppose there is a 2D rectangular uniform mesh, which has M points in the
x-direction and N points in the y-direction. Please describe in detail how to
carry out a checkerboard block decomposition of the mesh into S ×T blocks,
as evenly as possible. Note that M may not be divisible by S, and N may
not be divisible by T.


E.g 10x10 mesh with S = 3, T = 3. Meaning dividing M into 3 partitions and N into 3 partitions.
So we can divide into 4x4 and 3x3 blocks.

Partition P_ij  with size k_i x k_j 
k_i = [M/S] + e_i where e_i is the remainder. Is 1 if i < M modulus S, else 0.
Meaning the first partition dimensions will be larger than the last, if not perfectly divisible.

