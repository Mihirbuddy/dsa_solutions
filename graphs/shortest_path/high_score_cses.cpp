/*

https://cses.fi/problemset/task/1673


You play a game consisting of n rooms and m tunnels. Your initial score is 0, and each tunnel increases your score by x where x may be both positive or negative. You may go through a tunnel several times.
Your task is to walk from room 1 to room n. What is the maximum score you can get?
Input
The first input line has two integers n and m: the number of rooms and tunnels. The rooms are numbered 1,2,\dots,n.
Then, there are m lines describing the tunnels. Each line has three integers a, b and x: the tunnel starts at room a, ends at room b, and it increases your score by x. All tunnels are one-way tunnels.
You can assume that it is possible to get from room 1 to room n.
Output
Print one integer: the maximum score you can get. However, if you can get an arbitrarily large score, print -1.
Constraints

1 \le n \le 2500
1 \le m \le 5000
1 \le a,b \le n
-10^9 \le x \le 10^9

Example
Input:
4 5
1 2 3
2 4 -1
1 3 -2
3 4 7
1 4 4

Output:
5


try this example also

5 5
1 2 2
2 5 2
3 4 2
4 3 2
4 2 2

see here 3 and 4 are not reachable by source node hence there distance is still neg_inf and hence they will not update 2

 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
typedef long long ll;
typedef pair<ll, int> p;
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<ll>> edges;
  vector<int> visited(n + 1, 0);
  vector<int> indegree(n + 1, 0);
  unordered_map<int, vector<int>> adj;

  for (int i = 0; i < m; i++)
  {

    ll a, b, c;
    cin >> a >> b >> c;

    edges.push_back({a, b, c});
    adj[a].push_back(b);
    indegree[a]++;
  }
  const ll NEG_INF = -(1LL << 60);
  vector<ll> dist(n + 1, NEG_INF);
  dist[1] = 0;
  for (int i = 0; i < n - 1; i++)
  {
    for (auto &it : edges)
    {
      ll u = it[0];
      ll v = it[1];
      ll w = it[2];

      if (dist[u] != NEG_INF && dist[v] < dist[u] + w)
        dist[v] = dist[u] + w;

      // cout << u << " " << v << " " << w << "=" << dist[v] << endl;
    }
  }

  cout << "dist array" << endl;
  for (int i = 1; i <= n; i++)
    cout << dist[i] << " ";
  cout << endl;

  long long ans = dist[n];

  set<int> cycle;
  for (auto &it : edges)
  {
    ll u = it[0];
    ll v = it[1];
    ll w = it[2];

    if (dist[u] != NEG_INF && dist[v] < dist[u] + w)
    {
      dist[v] = dist[u] + w;
      cycle.insert(v);
    }
  }

  // cout << "nodes in cycle" << endl;
  // for (auto &it : cycle)
  // {
  //   cout << it << " ";
  // }
  // cout << endl;

  queue<int> q;

  q.push(1);
  queue<int> q_cycle;

  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    if (visited[u] == 1)
      continue;
    visited[u] = 1;
    if (cycle.find(u) != cycle.end())
    {
      q_cycle.push(u);
    }

    for (auto &it : adj[u])
    {
      q.push(it);
    }
  }

  visited.assign(n + 1, 0);

  while (!q_cycle.empty())
  {
    int top = q_cycle.front();
    q_cycle.pop();
    // cout << "top " << top << endl;
    if (visited[top] == 1)
      continue;
    visited[top] = 1;

    if (top == n)
    {
      ans = -1;
      break;
    }

    for (auto &it : adj[top])
    {
      q_cycle.push(it);
    }
  }

  if (ans == -1)
    cout << "-1";

  else
  {
    cout << dist[n];
  }

  return 0;
}