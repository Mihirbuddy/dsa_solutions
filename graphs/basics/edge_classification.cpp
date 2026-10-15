#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void dfs(int node, unordered_map<int, vector<int>> &adj, int &timer, vector<int> &visited, vector<int> &tin, vector<int> &tout)
{

  tin[node] = ++timer;
  visited[node] = 1;

  for (auto &it : adj[node])
  {
    if (visited[it] == 0)
    {
      // gray to white -> tree edge
      cout << node << "->" << it << " tree edge\n";
      dfs(it, adj, timer, visited, tin, tout);
    }
    else if (visited[it] == 1)
    {
      // gray to gray ->back edge
      cout << node << "->" << it << " back edge\n";
    }
    else
    {
      // it is black -> either forward or cross
      // if it is descendent of node only then forward edge
      if (tin[node] < tin[it])
      {
        cout << node << "->" << it << " forward edge\n";
      }
      else
      {
        cout << node << "->" << it << " cross edge\n";
      }
    }
  }
  tout[node] = ++timer;
  visited[node] = 2;
  return;
}

void classify_edge(unordered_map<int, vector<int>> &adj, int v, int e)
{

  vector<int> tin(v, -1);
  vector<int> tout(v, -1);
  vector<int> visited(v, 0);

  int timer = 0;

  for (int i = 0; i < v; i++)
  {
    if (visited[i] == 0)
    {

      dfs(i, adj, timer, visited, tin, tout);
    }
  }
}
int main()
{

  int t;
  cin >> t;
  while (t--)
  {
    int v;
    int e;
    cin >> v >> e;

    unordered_map<int, vector<int>> adj;

    for (int i = 0; i < e; i++)
    {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
    }

    cout << "testcase-" << t << endl;
    classify_edge(adj, v, e);
    cout << endl;
  }

  return 0;
}