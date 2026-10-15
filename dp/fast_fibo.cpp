#include <bits/stdc++.h>

using namespace std;

int mod = 1e9 + 7;

long long solve(long long n)
{

  if (n < 0)
    return 0;
  if (n == 0 || n == 1)
    return n;

  if (n == 2)
    return 1;

  if (n % 2 == 0)
  {
    long long prev = solve((n / 2) + 1) % mod;
    long long next = solve((n / 2) - 1) % mod;

    return (((prev * prev) % mod) - ((next * next) % mod) + mod) % mod;
  }

  else
  {
    long long prev = solve(n / 2) % mod;
    long long next = solve((n / 2) + 1) % mod;

    return ((prev * prev) % mod + (next * next) % mod) % mod;
  }
}

int main()
{

  long long n;
  cin >> n;

  cout << solve(n) << endl;
  return 0;
}