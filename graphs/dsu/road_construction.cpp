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
  int components;
  int maxi;

  DisjointSet(int n)
  {
    parent.resize(n);
    size.resize(n, 1);
    rank.resize(n, 1);
    components = n - 1;
    maxi = 1;

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

      if (size[u] > maxi)
        maxi = size[u];
    }

    else
    {
      parent[u] = v;
      size[v] += size[u];
      if (size[v] > maxi)
        maxi = size[v];
    }
    components -= 1;
  }
};

int main()
{

  int n, m;
  cin >> n >> m;

  DisjointSet ds(n + 1);

  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;

    ds.union_by_size(a, b);
    cout << ds.components << " " << ds.maxi << endl;
  }

  return 0;
}