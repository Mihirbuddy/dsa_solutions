#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void find_dist(int node, unordered_map<int, vector<int>> &adj, int n)
{

  queue<int> q;
  q.push(node);

  vector<int> dist(n + 1, 1e9);
  vector<int> parent(n + 1, -1);
  parent[node] = -1;
  dist[node] = 1;

  while (!q.empty())
  {
    int size = q.size();
    while (size--)
    {
      int top = q.front();
      q.pop();

      for (auto &it : adj[top])
      {
        if (dist[it] > 1 + dist[top])
        {
          q.push(it);
          parent[it] = top;
          dist[it] = 1 + dist[top];
        }
      }
    }
  }

  if (dist[n] == 1e9)
  {
    cout << "IMPOSSIBLE";
  }

  else
  {
    cout << dist[n] << endl;
    int x = n;
    vector<int> ans;
    while (x != -1)
    {
      ans.push_back(x);
      x = parent[x];
    }
    reverse(ans.begin(), ans.end());
    for (auto &it : ans)
      cout << it << " ";
  }
}

int main()
{

  int n, m;
  cin >> n >> m;

  unordered_map<int, vector<int>> adj;

  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  find_dist(1, adj, n);

  return 0;
}