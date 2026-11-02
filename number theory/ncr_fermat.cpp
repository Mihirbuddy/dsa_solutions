#include <iostream>
using namespace std;

typedef long long ll;

ll power(ll a, ll b, ll mod)
{
  if (b == 0)
    return 1;
  ll half = power(a, b / 2, mod);
  ll result = half * half % mod;
  if (b % 2 == 1)
    result = result * a % mod;
  return result;
}

int main()
{
  ll n, r, mod;
  cin >> n >> r >> mod;

  if (r < 0 || r > n)
  {
    cout << 0 << endl;
    return 0;
  }

  r = min(r, n - r);

  ll num = 1, den = 1;
  for (ll i = 0; i < r; i++)
  {
    num = num * ((n - i) % mod) % mod;
    den = den * ((i + 1) % mod) % mod;
  }

  cout << num * power(den, mod - 2, mod) % mod << endl;
  return 0;
}