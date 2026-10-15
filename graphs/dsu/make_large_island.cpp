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

int solve(vector<vector<int>> &grid, int n, int m)
{
  DisjointSet ds(n * m + 1);
  queue<pair<int, int>> q;

  vector<vector<int>> visited(n, vector<int>(m, 0));
  queue<pair<int, int>> q2;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (grid[i][j] == 1)
      {
        q.push({i, j});
        visited[i][j] = 1;
      }
      else
      {
        q2.push({i, j});
      }
    }
  }

  int delrow[4] = {0, 1, 0, -1};
  int delcol[4] = {1, 0, -1, 0};

  while (!q.empty())
  {
    auto top = q.front();
    q.pop();

    int row = top.first;
    int col = top.second;
    int par = row * n + col;

    for (int i = 0; i < 4; i++)
    {
      int nrow = row + delrow[i];
      int ncol = col + delcol[i];
      int child = nrow * n + ncol;

      if (nrow >= 0 && nrow < n && ncol < m && ncol >= 0 && grid[nrow][ncol] == 1 && visited[nrow][ncol] == 0)
      {
        visited[nrow][ncol] = 1;
        par = ds.find_parent(par);
        child = ds.find_parent(child);
        q.push({nrow, ncol});

        if (par == child)
        {
          continue;
        }
        else
        {
          ds.union_by_size(par, child);
        }
      }
    }

    int maxans = 0;

    while (!q2.empty())
    {
      auto top = q2.front();
      q2.pop();

      int row = top.first;
      int col = top.second;
      int par = row * n + col;

      int size = 1;
      set<int> mp;
      for (int i = 0; i < 4; i++)
      {
        int nrow = row + delrow[i];
        int ncol = col + delcol[i];
        int child = nrow * n + col;

        if (nrow >= 0 && nrow < n && ncol < m && ncol >= 0 && grid[nrow][ncol] == 1)
        {
          child = ds.find_parent(child);
          if (mp.find(child) == mp.end())
          {
            mp.insert(child);
            size += ds.size[child];
          }
        }
      }

      maxans = max(maxans, size);
    }

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 1)
        {
          int ele = i * n + j;
          if (ele == ds.parent[ele])
          {
            maxans = max(maxans, ds.size[ele]);
          }
        }
      }
    }

    return maxans;
  }
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

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        cin >> grid[i][j];
      }
    }

    cout << solve(grid, n, m);
    cout << endl;
  }

  return 0;
}
