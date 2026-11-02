#include <iostream>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b, ll &x, ll &y)
{
  if (b == 0) { x = 1; y = 0; return a; }
  ll x1, y1;
  ll g = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return g;
}

ll modInverse(ll a, ll m)
{
  ll x, y;
  ll g = gcd(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
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

  ll inv = modInverse(den, mod);
  if (inv == -1)
  {
    cout << "not possible" << endl;
    return 0;
  }

  cout << num * inv % mod << endl;
  return 0;
}