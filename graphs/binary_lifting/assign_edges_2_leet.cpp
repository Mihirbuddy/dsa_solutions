// vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries)

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int row, col;
vector<vector<int>> dp;
vector<int> depth;
vector<long long> power2;

const long long MOD = 1e9 + 7;

void calculate_power2()
{
  power2[0] = 1;
  for (int i = 1; i < (int)power2.size(); i++)
    power2[i] = (2LL * power2[i - 1]) % MOD;
}

void dfs(int node, vector<vector<int>> &adj, int parent, int d)
{

  depth[node] = d;
  dp[node][0] = parent;

  for (auto nbr : adj[node])
  {
    if (nbr == parent)
      continue;
    dfs(nbr, adj, node, d + 1);
  }
}

void build_dp()
{

  for (int j = 1; j < col; j++)
  {
    for (int i = 1; i < row; i++)
    {
      if (dp[i][j - 1] == -1)
        continue;
      dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
  }
}

int find_lca(int a, int b)
{

  // we will not make 2 cases like depth[a]>depth[b] and depth[a]<depth[b], instead we will only make 1 case depth[a]<depth[b]

  if (depth[a] != depth[b])
  {
    if (depth[a] > depth[b])
    {
      a = a + b;
      b = a - b;
      a = a - b;
    }

    // bringing them to the same level
    int diff = depth[b] - depth[a];

    for (int j = 0; j < col; j++)
    {
      if (diff & (1LL << j))
      {
        b = dp[b][j];
      }
    }
  }

  if (a == b)
    return a;

  for (int j = col - 1; j >= 0; j--)
  {
    if (dp[a][j] != -1 && dp[b][j] != -1 &&
        dp[a][j] != dp[b][j])
    {
      a = dp[a][j];
      b = dp[b][j];
    }
  }

  return dp[a][0];
}

int main()
{

  int n, q;
  cin >> n >> q;

  // there are n-1 edges
  vector<vector<int>> adj(n + 1);

  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<vector<int>> queries;

  for (int i = 0; i < q; i++)
  {

    int a, b;
    cin >> a >> b;

    queries.push_back({a, b});
  }

  row = n + 1;
  col = 1;
  while ((1LL << col) <= n)
    col++;

  dp.assign(row, vector<int>(col, -1));

  depth.assign(n + 1, 0);

  dfs(1, adj, -1, 0);
  build_dp();

  vector<long long> ans;

  power2.assign(row, 1);

  calculate_power2();

  for (auto &it : queries)
  {
    int u = it[0];
    int v = it[1];

    if (u == v)
    {
      ans.push_back(0);
      continue;
    }

    else
    {
      int node = find_lca(u, v);
      int dist = depth[u] + depth[v] - 2 * depth[node];
      long long result = power2[dist - 1];
      ans.push_back(result);
    }
  }

  for (auto &it : ans)
  {
    cout << it << " ";
  }

  return 0;
}