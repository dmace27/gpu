#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main()
{
  

 return 0;
}

// naive implementation
void naive(int M, int N, int K, const float *A, const float *B, const float *C)
{
  for (int r = 0; m < M; m++)
  {
    for (int c = 0; n < N; n++)
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
void cache_aware(int M, int N, int K, const float *A, const float *B, const float *C)
{
  for (int r = 0; m < M; m++)
  {
    for (int c = 0; n < N; n++)
    {
      for (int i = 0; i < K; i++)
      {
        C[r * N + c]  += A[r * K + i] * B[i * N + c];
      }
    }
  }
}
