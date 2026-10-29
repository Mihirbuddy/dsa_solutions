#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

int find_parent(int node, vector<int> &parent)
{

  if (node == parent[node])
    return node;

  return parent[node] = find_parent(parent[node], parent);
}

void dfs(int node, unordered_map<int, vector<int>> &adj, stack<int> &s, vector<int> &visited)
{

  visited[node] = 1;
  for (auto &it : adj[node])
  {
    if (visited[it] == 0)
    {
      dfs(it, adj, s, visited);
    }
  }

  s.push(node);
}

void dfs2(int id, int node, unordered_map<int, vector<int>> &adj, vector<int> &parent, vector<int> &visited)
{

  visited[node] = 1;
  parent[node] = id;

  for (auto &it : adj[node])
  {
    if (!visited[it])
    {
      dfs2(id, it, adj, parent, visited);
    }
  }
}

int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  unordered_map<int, vector<int>> adj;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  stack<int> s;

  vector<int> visited(n + 1, 0);

  for (int i = 1; i <= n; i++)
  {
    if (visited[i] == 0)
    {
      dfs(i, adj, s, visited);
    }
  }

  unordered_map<int, vector<int>> adjt;
  visited.assign(n + 1, 0);

  for (auto &it : adj)
  {
    for (auto &it1 : it.second)
    {
      adjt[it1].push_back(it.first);
    }
  }

  vector<int> parent(n + 1);
  for (int i = 0; i <= n; i++)
  {
    parent[i] = i;
  }
  int id = 0;

  while (!s.empty())
  {
    int node = s.top();
    s.pop();

    if (visited[node])
      continue;

    id += 1;
    dfs2(id, node, adjt, parent, visited);
  }

  cout << id << endl;
  for (int i = 1; i <= n; i++)
  {
    cout << parent[i] << " ";
  }

  return 0;
}