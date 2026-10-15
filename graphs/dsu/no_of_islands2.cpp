#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <set>

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

int delrow[4] = {0, 1, 0, -1};
int delcol[4] = {1, 0, -1, 0};

int solve(vector<vector<int>> &grid, int x, int y, int n, int m, int &count, DisjointSet &ds)
{
  int par = x * n + y;

  grid[x][y] = 1;
  for (int i = 0; i < 4; i++)
  {
    int row = x + delrow[i];
    int col = y + delcol[i];

    if (row >= 0 && row < n && col >= 0 && col < m && grid[row][col] == 1)
    {
      int child = row * n + col;
      if (ds.parent[par] != ds.parent[child])
      {
        ds.union_by_size(par, child);
        count -= 1;
      }
    }
  }
  count+=1;
  return count + 1;
}
int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    int n;
    cin >> n;
    int m;
    cin >> m;
    DisjointSet ds(n * m + 1);

    vector<vector<int>> grid(n, vector<int>(m, 0));

    int q;
    cin >> q;

    vector<int> ans;
    int count = 0;

    for (int i = 0; i < q; i++)
    {
      int x, y;
      cin >> x >> y;

      int result = solve(grid, x, y, n, m, count, ds);
      ans.push_back(result);
    }

    for (auto &it : ans)
    {
      cout << it << " ";
    }

    cout << endl;
  }

  return 0;
}
