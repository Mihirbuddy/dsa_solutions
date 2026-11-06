#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<ll, int> p;

const ll inf = 1e18;
int main()
{
  int n, m, k;

  cin >> n >> m >> k;

  unordered_map<int, vector<vector<int>>> adj;

  // roads

  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;

    adj[u].push_back({v, w, i + 1});
    adj[v].push_back({u, w, i + 1});
  }

  // trains
  for (int i = 0; i < k; i++)
  {
    int u, w;
    cin >> u >> w;

    adj[1].push_back({u, w, i + m + 1});
    adj[u].push_back({1, w, i + m + 1});
  }

  vector<ll> dist(n + 1, inf);
  vector<int> id(n + 1, -1);

  priority_queue<p, vector<p>, greater<p>> pq;

  pq.push({0, 1});

  while (!pq.empty())
  {

    auto top = pq.top();
    pq.pop();

    ll step = top.first;
    int node = top.second;

    if (step > dist[node])
      continue;

    for (auto nbr : adj[node])
    {
      int nbr_node = nbr[0];
      ll nbr_step = nbr[1];
      int route = nbr[2];

      if (step + nbr_step < dist[nbr_node])
      {
        dist[nbr_node] = step + nbr_step;
        id[nbr_node] = route;

        pq.push({dist[nbr_node], nbr_node});
      }
      else if (1ll * step + nbr_step == dist[nbr_node] && id[nbr_node] > m && route <= m)
      {
        dist[nbr_node] = 1ll * step + nbr_step;
        id[nbr_node] = route;
      }
    }
  }

  set<int> st;
  for (auto it : id)
  {
    if (it > m)
    {
      st.insert(it);
    }
  }

  int cnt = st.size();

  int ans = k - cnt;

  cout << ans << endl;

  return 0;
}