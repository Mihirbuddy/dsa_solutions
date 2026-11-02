#include <iostream>
using namespace std;

// Returns floor(sqrt(n)) for n >= 0
long long integerSqrt(long long n)
{
  if (n < 2)
    return n;                       // 0 aur 1 handle

  long long low = 1;
  long long high = n / 2 + 1;       // sqrt(n) isse chhota hi hota hai
  long long ans = 1;

  while (low <= high)
  {
    long long mid = low + (high - low) / 2;

    // mid * mid <= n ki jagah mid <= n / mid, taaki overflow na ho
    if (mid <= n / mid)
    {
      ans = mid;
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  return ans;
}

int main()
{
  long long n;

  cout << "Enter a non-negative integer: ";
  if (!(cin >> n))
  {
    cerr << "Error: invalid input. Please enter an integer.\n";
    return 1;
  }

  if (n < 0)
  {
    cerr << "Error: square root of a negative number is not defined.\n";
    return 1;
  }

  cout << integerSqrt(n) << "\n";
  return 0;
}