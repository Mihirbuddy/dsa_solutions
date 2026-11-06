#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int main()
{

  int n, m;
  cin >> n >> m;

  unordered_map<int, vector<pair<int, int>>> adj;

  const int inf = 1e9;

  int node = -1;
  int mini_node = inf;
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;

    u = u - 1;
    v = v - 1;

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});

    if (w < mini_node)
    {
      node = u;
      mini_node = w;
    }
  }

  // cout << "this is the starting node" << node << endl;

  vector<int> parent(n, -1);
  vector<int> key(n, inf);
  vector<bool> mst(n);

  key[node] = 0;

  int sum = 0;

  for (int j = 0; j < n; j++)
  {
    int mini = inf;
    int u = -1;

    for (int i = 0; i < n; i++)
    {
      if (!mst[i] && key[i] < mini)
      {
        mini = key[i];
        u = i;
      }
    }

    if (u == -1)
    {
      sum = -1;
      break;
    }

    mst[u] = true;
    sum += mini;

    // cout << "this is the " << j + 1 << " node selected " << u << " with mini " << mini << endl;

    for (auto &it : adj[u])
    {
      int nbr = it.first;
      int wgt = it.second;
      if (!mst[nbr] && key[nbr] > wgt)
      {
        key[nbr] = wgt;
        parent[nbr] = u;
      }
    }
  }

  if (sum == -1)
  {
    cout << "IMPOSSIBLE" << endl;
  }

  else
    cout << sum << endl;

  return 0;
}