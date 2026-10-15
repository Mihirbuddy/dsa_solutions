#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void dfs(int node, unordered_map<int, vector<int>> &adj, vector<int> &visited)
{
  visited[node] = 1;

  for (auto &it : adj[node])
  {
    if (!visited[it])
      dfs(it, adj, visited);
  }
}

vector<int> find_topo(int n, vector<int> &indegree, unordered_map<int, vector<int>> &adj)
{
  queue<int> q;

  for (int i = 1; i <= n; i++)
  {
    if (indegree[i] == 0)
      q.push(i);
  }
  vector<int> ans;

  while (!q.empty())
  {

    int size = q.size();
    while (size--)
    {
      int top = q.front();
      q.pop();

      ans.push_back(top);

      for (auto &it : adj[top])
      {
        indegree[it]--;
        if (indegree[it] == 0)
        {
          q.push(it);
        }
      }
    }
  }

  return ans;
}
int main()
{

  int n, m;
  cin >> n >> m;

  vector<int> indegree(n + 1, 0);
  unordered_map<int, vector<int>> adj;

  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    indegree[v]++;
  }

  vector<int> visited(n + 1, 0);
  dfs(1, adj, visited);

  if (!visited[n])
  {
    cout << "IMPOSSIBLE";
    return 0;
  }
  vector<int> topo = find_topo(n, indegree, adj);

  vector<long long> count(n + 1, 0);

  count[1] = 1;

  int mod = 1e9 + 7;

  for (int i = 0; i < n; i++)
  {

    int u = topo[i];

    if (!visited[u])
      continue;

    for (auto &it : adj[u])
    {
      count[it] = (count[it] + count[u]) % mod;
    }
  }

  cout << count[n];

  return 0;
}