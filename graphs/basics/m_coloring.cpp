#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool ispossible(int node, vector<int> &colors, unordered_map<int, vector<int>> &adj, int color)
{

  for (auto &it : adj[node])
  {
    if (colors[it] == color)
      return false;
  }
  return true;
}
bool solve(int v, int node, vector<int> &colors, unordered_map<int, vector<int>> &adj, int m)
{

  if (node == v)
    return true;

  for (int i = 0; i < m; i++)
  {
    if (ispossible(node, colors, adj, i))
    {
      colors[node] = i;
      if (solve(v, node + 1, colors, adj, m))
        return true;
      colors[node] = -1;
    }
  }

  return false;
}
bool possible(int v, unordered_map<int, vector<int>> &adj, int m)
{
  vector<int> colors(v, -1);

  return solve(v, 0, colors, adj, m);
}
int main()
{

  int vertex;
  cin >> vertex;

  int m;
  cin >> m;

  unordered_map<int, vector<int>> adj;
  int n;
  cin >> n;

  for (int i = 0; i < n; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  bool result = possible(vertex, adj, m);

  result ? cout << "true" : cout << "false";
  return 0;
}