/*
3 4
1 2 6
1 3 2
3 2 3
1 3 4
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
typedef pair<ll, int> p;
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n + 1);
  vector<int> visited(n + 1, 0);

  for (int i = 0; i < m; i++)
  {

    int a, b, c;
    cin >> a >> b >> c;

    adj[a].push_back({b, c});
  }

  vector<ll> dist(n + 1, -1);

  // queue<pair<int,int>> q;
  priority_queue<p, vector<p>, greater<p>> q;
  q.push({0, 1});

  dist[1] = 0;

  while (!q.empty())
  {
    auto top = q.top();
    q.pop();
    int node = top.second;
    ll d = top.first;
    if (visited[node])
      continue;
    visited[node] = 1;

    for (auto &it : adj[node])
    {

      if (dist[it.first] == -1 || d + it.second < dist[it.first])
      {
        dist[it.first] = d + it.second;
        q.push({dist[it.first], it.first});
      }
    }
  }

  for (int i = 1; i <= n; i++)
  {
    cout << dist[i] << " ";
  }
  return 0;
}