#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef __int128 LL;

ll gcd(ll a, ll b, ll &x, ll &y)
{
  if (b == 0) { x = 1; y = 0; return a; }
  ll x1, y1;
  ll g = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return g;
}

ll mod_inverse(ll a, ll m)
{
  ll x, y;
  ll g = gcd(a % m, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}

// moduli pairwise coprime hone chahiye, warna -1 return karta hai
ll crt(vector<ll> &a, vector<ll> &m, int n)
{
  ll M = 1;
  for (ll val : m) M *= val;

  ll x = 0;
  for (int i = 0; i < n; i++)
  {
    ll Mi = M / m[i];
    ll inv = mod_inverse(Mi, m[i]);
    if (inv == -1) return -1;

    ll ai = ((a[i] % m[i]) + m[i]) % m[i];          // negative a ke liye
    LL term = (LL)Mi * ai % M * inv % M;
    x = (ll)(((LL)x + term) % M);
  }
  return x;
}

int main()
{
  int n;
  cin >> n;

  vector<ll> a(n), m(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> m[i];

  ll res = crt(a, m, n);
  if (res == -1)
    cout << "moduli pairwise coprime nahi hain" << endl;
  else
    cout << "the crt is " << res << endl;
  return 0;
}