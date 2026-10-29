#include <iostream>

using namespace std;

typedef long long ll;

ll findncr(int n, int r)
{

  if (r < 0 || r > n)
    return 0;

  if (r > n - r)
    r = n - r;

  ll ans = 1;
  for (int i = 1; i <= r; i++)
  {
    ans = ans * (n - i + 1) / i;
  }

  return ans;
}

ll findnpr(int n, int r)
{

  if (r < 0 || r > n)
    return 0;

  ll ans = 1;
  for (int i = 0; i < r; i++)
  {
    ans = ans * (n - i);
  }
  return ans;
}
int main()
{

  int t;
  cin >> t;
  while (t--)
  {
    int n;
    int r;
    cin >> n >> r;

    cout << "the combination is " << findncr(n, r) << endl;
    cout << "the permutation is " << findnpr(n, r) << endl;

    cout << endl;
  }
  return 0;
}