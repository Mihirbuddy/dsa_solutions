#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

void dfs(int node, unordered_map<int, vector<pair<int, int>>> &adj, unordered_map<int, int> &v1, int stop, int xo, int parent)
{

  if (node == stop)
    return;

  v1[node] = xo;

  for (auto &nbr : adj[node])
  {

    int nbr_node = nbr.first;
    int dist = nbr.second;

    if (nbr_node == parent)
      continue;
    dfs(nbr_node, adj, v1, stop, xo ^ dist, node);
  }
}

int main()
{
  int t;
  cin >> t;

  while (t--)
  {

    int n, a, b;
    cin >> n >> a >> b;

    unordered_map<int, vector<pair<int, int>>> adj;

    for (int i = 0; i < n - 1; i++)
    {
      int u, v, w;
      cin >> u >> v >> w;

      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }

    unordered_map<int, int> v1(n);
    unordered_map<int, int> v2(n);

    dfs(a, adj, v1, b, 0, -1);

    dfs(b, adj, v2, -1, 0, -1);

    set<int> s;
    for (auto &it : v2)
    {
      int node = it.first;
      int dist = it.second;
      if (node == b || dist == -1)
        continue;
      s.insert(dist);
    }

    bool ans = false;
    for (auto &it : v1)
    {
      int node = it.first;
      int dist = it.second;

      if (s.count(dist) > 0)
      {
        ans = true;
        break;
      }
    }

    if (ans)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}