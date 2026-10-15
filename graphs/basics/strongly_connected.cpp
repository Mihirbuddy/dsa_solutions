#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;

void dfs(int node, unordered_map<int, vector<int>> &adj, vector<int> &visited, stack<int> &s)
{

  visited[node] = 1;

  for (auto &nbr : adj[node])
  {
    if (visited[nbr] == 0)
    {
      dfs(nbr, adj, visited, s);
    }
  }
  s.push(node);
}

void dfs2(int node, unordered_map<int, vector<int>> &adj, vector<int> &visited)
{
  visited[node] = 1;

  for (auto &nbr : adj[node])
  {
    if (visited[nbr] == 0)
    {
      dfs2(nbr, adj, visited);
    }
  }
}

int main()
{
  int v, e;
  cin >> v >> e;

  int count = 0;
  unordered_map<int, vector<int>> adj;
  for (int i = 0; i < e; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
  }
  vector<int> visited(v + 1, 0);
  stack<int> s;
  for (int i = 0; i < v; i++)
  {
    if (visited[i] == 0)
    {
      dfs(i, adj, visited, s);
    }
  }

  // building transposed adj

  unordered_map<int, vector<int>> adjT;
  for (auto &it : adj)
  {
    for (auto &nbr : it.second)
    {
      adjT[nbr].push_back(it.first);
    }
  }

  vector<int> visited2(v + 1, 0);

  while (!s.empty())
  {
    int top = s.top();
    s.pop();

    if (visited2[top] == 0)
    {
      count++;
      dfs2(top, adjT, visited2);
    }
  }

  cout << count;
  return 0;
}
