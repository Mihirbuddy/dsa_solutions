#include <bits/stdc++.h>
using namespace std;

void solve()
{
  int n, k;
  cin >> n >> k;

  vector<int> arr(n);
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  multiset<int> s;

  for (int i = 0; i < n; i++)
  {
    s.insert(arr[i]);

    if (i >= k)
    {
      s.erase(s.find(arr[i - k]));
    }

    if (i >= k - 1)
    {
      auto it = s.begin();
      advance(it, (k - 1) / 2);
      cout << *it << " ";
    }
  }
  cout << "\n";
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
}