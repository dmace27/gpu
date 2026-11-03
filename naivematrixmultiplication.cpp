#include <iostream>
#include <algorithm>
#include <vector>
// reading these: 
// https://siboehm.com/articles/22/Fast-MMM-on-CPU
// https://easonhuang.dev/blog/optimizing_matmul

int main()
{
 return 0;
}

// naive implementation
void naive(int M, int N, int K, const float *A, const float *B, const float *C)
{
  for (int r = 0; r < M; m++)
  {
    for (int c = 0; c < N; n++)
    {
      float acc = 0.0f;

      for (int i = 0; i < K; i++)
      {
        acc += A[r * K + i] * B[i * N + c];
      }
      C[r * N + c] = acc;
    }
  }
}

// cachce aware implementation
// re order the inner most two loops     
// because the rows are far away from each other in  
// physical continguous memory
void cache_aware(int M, int N, int K, const float *A, const float *B, const float *C)
{
  for (int r = 0; r < M; m++)
  {
    for (int i = 0; i < K; i++)
    {
      for (int c = 0; c < N; c++)
      {
        C[r * N + c] += A[r * k + i] * B[i * N + c];
      }
    }
  }
}

// cache aware with tiling
//
// The above algorithm still struggles with very large matrices
// because the size exceeds the space on the L1/L2 cache
// Here we break up the matrices into smaller pieces that can fit on the cache 
// I have a macbook pro (ik not the best for gpu work but well figure something out)
// so i want to implement 64x64 blocks

void tiling(int M, int N, int K, const float *A, const float *B, const float *C)
{

  const int size = 64; // size of the block

  // initialize the whole thing to zero
  for (int i = 0; i < M * N; i++)
  {
    C[i] = 0.0f;
  }
  
  // outer loops
  for (int rr = 0; rr < M; rr += size)
  {
    for (int ii = 0; ii < K; ii += size)
    {
      for (int cc = 0; cc < N; cc += size)
      {
        
        int r_max = std::min (rr + BS, M);
        int k_max = std::min (ii + BS, K);
        int c_max = std::min (cc + BS, N);

        for (int r = rr; r < r_max; r++)
        {

          for (int i = ii; i < k_max; i++)
          {

            float a_val = A[r * K + i]; // temporarily store (cache) the a value
            // so that the memory doesn't have to keep jumping around

            for (int c = cc; c < c_max; c++)
            {

              C[r * N + c] += a_val * B[i * N + c];
            }
          }
        }
      }
    }
  }
}
