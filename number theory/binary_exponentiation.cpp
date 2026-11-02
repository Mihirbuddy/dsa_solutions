#include <iostream>

using namespace std;

typedef long long ll;

typedef long long ll;
typedef __int128 LL;

ll solve(ll a, ll b, ll mod)
{
  if (b == 0)
    return 1 % mod;

  ll half = solve(a, b / 2, mod);
  ll result = (ll)((LL)half * half % mod);       // mod ke saath square

  if (b % 2 == 1)
    result = (ll)((LL)(a % mod) * result % mod); // mod ke saath ek aur a

  return result;
}

int main()
{

  int t;
  cin >> t;
  while (t--)
  {
    int a, b;
    cin >> a >> b;


   bool inv=false;
    if(b<0){
      inv=true;
      b=-b;
    }

    ll ans = solve(a, b);
    if(inv){
      float result=1.0/ans;
      cout<<result<<endl;
    }
    else{
      cout<<ans;
    }
  }

  return 0;
}