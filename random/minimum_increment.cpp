#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
// #include<bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> arr(n);

  unordered_map<int, int> umap;
  for (int i = 0; i < n; i++)
  {
    int ele;
    cin >> ele;
    arr[i] = ele;
    umap[ele]++;
  }

  long long ans = 0;
  sort(arr.begin(), arr.end());
  int max_one_more = 1;
  for (int i = 0; i < n; i++)
  {
    int ele = arr[i];

    if (umap[ele] <= 1)
      continue;

    else
    {
      bool flag = false;
      // int one_less = ele - 1;
      int one_more = ele + 1;
      if (one_more <= max_one_more)
      {
        flag = true;
        one_more = max_one_more;
      }

      while (umap.find(one_more) != umap.end())
        one_more++;

      if (flag)
        max_one_more = one_more + 1;
      int diff2 = abs(ele - one_more);

      ans += diff2;
      umap[one_more]++;
      umap[ele]--;
    }
  }

  cout << ans;

  return 0;
}