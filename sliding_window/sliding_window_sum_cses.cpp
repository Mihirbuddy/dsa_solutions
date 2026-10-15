/*
You are given an array of n integers. Your task is to calculate the sum of each window of k elements, from left to right.
In this problem the input data is large and it is created using a generator.
Input
The first line contains two integers n and k: the number of elements and the size of the window.
The next line contains four integers x, a, b and c: the input generator parameters. The input is generated as follows:

x_1=x
x_i=(ax_{i-1}+b) \bmod c for i=2,3,\dots,n

Output
Print the xor of all window sums.
Constraints

1 <= k <= n <= 10^7
0 <= x, a, b <= 10^9
1 <= c <= 10^9

Example
Input:
8 5
3 7 1 11

Output:
12

Explanation: The input array is [3,0,1,8,2,4,7,6]. The windows are [3,0,1,8,2], [0,1,8,2,4], [1,8,2,4,7] and [8,2,4,7,6], and their sums are 14, 15, 22 and 27. Thus, the answer is 14 ^ 15 ^ 22 ^ 27 = 12.
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{

  int n, k;
  cin >> n >> k;

  long long x, a, b, c;
  cin >> x >> a >> b >> c;

  vector<long long> arr(n);

  if (n >= 0)
    arr[0] = x;

  for (int i = 1; i < n; i++)
  {
    arr[i] = (1LL * a * arr[i - 1] + b) % c;
  }

  long long sum = 0;

  for (int i = 0; i < k; i++)
  {
    sum += arr[i];
  }

  long long result = sum;

  for (int i = k; i < n; i++)
  {
    sum -= arr[i - k];
    sum += arr[i];

    result ^= sum;
  }

  cout << result;

  return 0;
}