// #include<bits/stdc++.h>

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{

  int n;
  cin >> n;
  vector<int> arr(n);

  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  vector<int> ans(n);
  priority_queue<int> pq;

  for (int i = n - 1; i >= 0; i--)
  {
    int ele = arr[i];
    vector<int> temp;
    while (!pq.empty() && pq.top() >= ele)
    {
      temp.push_back(pq.top());
      pq.pop();
    }

    ans[i] = pq.size();
    while (temp.size() > 0)
    {
      pq.push(temp.back());
      temp.pop_back();
    }
    pq.push(arr[i]);
  }

  for (int i = 0; i < n; i++)
    cout << ans[i] << " ";

  return 0;
}