#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int timer_ = 0;

void dfs(int u, int parentEdge,
         vector<vector<pair<int, int>>> &adj,
         vector<bool> &visited,
         vector<int> &tin,
         vector<int> &low,
         vector<pair<int, int>> &bridges)
{
  visited[u] = true;
  tin[u] = low[u] = ++timer_;

  for (auto [v, id] : adj[u])
  {
    if (id == parentEdge)
      continue; // don't go back through the same edge

    if (visited[v])
    {
      // Back edge: u can reach the ancestor v directly
      low[u] = min(low[u], tin[v]);
    }
    else
    {
      dfs(v, id, adj, visited, tin, low, bridges);

      // After returning, v's subtree may reach higher up
      low[u] = min(low[u], low[v]);

      // v's subtree cannot reach u or above except via this edge
      if (low[v] > tin[u])
        bridges.push_back({u, v});
    }
  }
}

int main()
{
  int V, E;
  cin >> V >> E;

  vector<vector<pair<int, int>>> adj(V);
  for (int i = 0; i < E; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back({v, i});
    if (u != v)
      adj[v].push_back({u, i});
  }

  vector<bool> visited(V, false);
  vector<int> tin(V, 0), low(V, 0);
  vector<pair<int, int>> bridges;

  for (int i = 0; i < V; i++)
    if (!visited[i])
      dfs(i, -1, adj, visited, tin, low, bridges);

  cout << "Bridges: " << bridges.size() << "\n";
  for (auto [u, v] : bridges)
    cout << u << " - " << v << "\n";

  return 0;
}