#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class DisjointSet
{

public:
  vector<int> size;
  vector<int> parent;
  DisjointSet(int n)
  {
    parent.resize(n);
    size.resize(n, 1);

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
  int n;
  cin >> n;

  int maxrow = 0;
  int maxcol = 0;

  vector<vector<int>> grid;
  for (int i = 0; i < n; i++)
  {
    int u, v;
    cin >> u >> v;

    grid.push_back({u, v});
    maxrow = max(maxrow, u);
    maxcol = max(maxcol, v);
  }

  DisjointSet ds(maxrow + maxcol + 1);
  unordered_map<int, int> stones_removed;

  for (auto &it : grid)
  {
    int row = it[0];
    int col = it[1] + maxrow + 1;

    row = ds.find_parent(row);
    col = ds.find_parent(col);

    if (row == col)
      continue;
    else
    {
      ds.union_by_size(row, col);
    }

    stones_removed[row] = 1;
    stones_removed[col] = 1;
  }

  int cnt;
  for (auto &stones : stones_removed)
  {
    if (stones.first == ds.find_parent(stones.first))
    {
      cnt++;
    }
  }
  cout << n - cnt;

  return 0;
}
