/*
Given a weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by a 2d array edges[][], where edges[i] = [u, v, w] represents a direct edge from node u to v having w edge weight. You are also given a source vertex src.

Compute the shortest distances from the src to all other vertices. If a vertex is unreachable from the src, its distance should be marked as 108. Additionally, if the graph contains a negative weight cycle, return [-1] to indicate that shortest paths cannot be reliably computed.

V = 5, edges[][] = [[1, 3, 2], [4, 3, -1], [2, 4, 1], [1, 2, 1], [0, 1, 5]], src = 0

5 5
0
1 3 2
4 3 -1
2 4 1
1 2 1
0 1 5
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
  int v, e;
  cin >> v >> e;

  int src;
  cin >> src;

  // unordered_map<int,vector<pair<int,int>>> adj;
  vector<int> dist(v, 1e8);

  dist[src] = 0;

  vector<vector<int>> edges;
  for (int i = 0; i < e; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({u, v, w});
  }

  for (int i = 0; i < v - 1; i++)
  {
    for (auto &it : edges)
    {
      int u = it[0];
      int v = it[1];
      int w = it[2];

      if (dist[u] == 1e8)
        continue;

      if (dist[v] == 1e8 || dist[v] > dist[u] + w)
      {
        dist[v] = dist[u] + w;
      }
    }
  }

  bool flag = false;
  for (auto &it : edges)
  {
    int u = it[0];
    int v = it[1];
    int w = it[2];

    if (dist[v] == 1e8 || dist[v] > dist[u] + w)
    {
      flag = true;
      break;
    }
  }

  if (flag == true)
    cout << "-1";
  else
  {
    for (auto &it : dist)
    {
      cout << it << " ";
    }
  }

  return 0;
}
