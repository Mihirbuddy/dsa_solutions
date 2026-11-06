#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int main()
{

  int n, m;
  cin >> n >> m;

  unordered_map<int, vector<pair<int, int>>> adj;

  const ll inf = 1e18;

  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;

    u = u - 1;
    v = v - 1;

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  // cout << "this is the starting node" << node << endl;

  vector<int> parent(n, -1);
  vector<ll> key(n, inf);
  vector<bool> mst(n);

  key[0] = 0;
  priority_queue<p, vector<p>, greater<p>> pq;
  pq.push({0, 0});
  ll sum = 0;

  while (!pq.empty())
  {

    auto top = pq.top();
    pq.pop();

    if (mst[top.second])
      continue;

    int u = top.second;
    ll mini = top.first;

    // cout << "this is the node selected " << u << " with mini " << mini << endl;

    mst[u] = true;
    sum += mini;

    for (auto &it : adj[u])
    {
      int nbr = it.first;
      int wgt = it.second;
      if (!mst[nbr] && key[nbr] > wgt)
      {
        key[nbr] = wgt;
        pq.push({key[nbr], nbr});
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    if (!mst[i])
    {
      sum = -1;
      break;
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