#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
long long maxi = (1LL << 60) - 1;
void solve(vector<vector<long long>> &dist, int n)
{

  for (int k = 1; k <= n; k++)
  {
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {

        if (dist[i][k] == maxi || dist[k][j] == maxi)
          continue;

        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}
int main()
{
  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, maxi));

  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;

    dist[a][b] = min(1LL * c, dist[a][b]);
    dist[b][a] = min(1LL * c, dist[b][a]);
  }

  for (int i = 1; i <= n; i++)
  {
    dist[i][i] = 0;
  }

  solve(dist, n);

  for (int i = 0; i < q; i++)
  {
    int a, b;
    cin >> a >> b;

    if (dist[a][b] == maxi)
      cout << "-1" << endl;
    else
      cout << dist[a][b] << endl;
  }
  return 0;
}