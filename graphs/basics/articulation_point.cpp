#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int timer_ = 0;

void dfs(int u, int parent,
         vector<vector<int>> &adj,
         vector<bool> &visited,
         vector<int> &tin,
         vector<int> &low,
         vector<bool> &isAP)
{
  visited[u] = true;
  tin[u] = low[u] = ++timer_;
  int children = 0;

  for (int v : adj[u])
  {
    if (v == parent)
      continue;

    if (visited[v])
    {
      // Back edge: u can reach the ancestor v directly
      low[u] = min(low[u], tin[v]);
    }
    else
    {
      dfs(v, u, adj, visited, tin, low, isAP);
      low[u] = min(low[u], low[v]);
      children++;

      // Non-root: child's subtree can't climb strictly above u
      if (parent != -1 && low[v] >= tin[u])
        isAP[u] = true;
    }
  }

  // Root: articulation point only if it has 2+ DFS children
  if (parent == -1 && children > 1)
    isAP[u] = true;
}

int main()
{
  int V, E;
  cin >> V >> E;

  vector<vector<int>> adj(V);
  for (int i = 0; i < E; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<bool> visited(V, false), isAP(V, false);
  vector<int> tin(V, 0), low(V, 0);

  for (int i = 0; i < V; i++)
    if (!visited[i])
      dfs(i, -1, adj, visited, tin, low, isAP);

  cout << "Articulation points:";
  for (int i = 0; i < V; i++)
    if (isAP[i])
      cout << " " << i;
  cout << "\n";

  return 0;
}