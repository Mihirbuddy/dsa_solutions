#include <iostream>

using namespace std;

typedef long long ll;

ll solve(int a, int b)
{

  
  if (b == 0)
    return 1;

  ll half = solve(a, b / 2);
  ll result = half * half;

  if (b % 2 == 1)
    result = a * result;

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