#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DisjointSet
{

public:
  vector<int> size;
  vector<int> rank;
  vector<int> parent;
  DisjointSet(int n)
  {
    parent.resize(n);
    size.resize(n, 1);
    rank.resize(n, 1);

    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
    }
  }

  int find_parent(int u)
  {
    if (u == parent[u])
      return u;

    return parent[u] = find_parent(parent[u]);
  }

  void union_by_rank(int u, int v)
  {
    u = find_parent(u);
    v = find_parent(v);

    if (u == v)
      return;

    else if (rank[u] >= rank[v])
    {
      parent[v] = u;
      rank[u] += rank[v];
    }

    else
    {
      parent[u] = v;
      rank[v] += rank[u];
    }
  }
  void union_by_size(int u, int v)
  {
    u = find_parent(u);
    v = find_parent(v);

    if (u == v)
      return;

    else if (size[u] >= size[v])
    {
      parent[v] = u;
      size[u] += size[v];
    }

    else
    {
      parent[u] = v;
      size[v] += size[u];
    }
  }
};
int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    int n;
    cin >> n;

    DisjointSet ds(n);

    int e;
    cin >> e;

    vector<vector<int>> grid;
    for (int i = 0; i < e; i++)
    {
      int u, v;
      cin >> u >> v;

      grid.push_back({u, v});
    }

    int extra = 0;

    for (auto &it : grid)
    {
      int u = it[0];
      int v = it[1];

      if (ds.find_parent(u) == ds.find_parent(v))
      {
        extra++;
      }
      else
      {
        ds.union_by_rank(u, v);
      }
    }

    int component = 0;

    for (int i = 0; i < n; i++)
    {
      if (i == ds.parent[i])
        component++;
    }

    int diff = component - extra;
    int ans;

    if (diff > 1)
      ans = -1;
    else
      ans = component - 1;

    cout << ans << endl;
  }
  return 0;
}
