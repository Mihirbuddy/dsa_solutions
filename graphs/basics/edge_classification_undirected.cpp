#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
see in undirected graph there is no forward edge and no cross edge , because see the edges are undirectted , so
what is forward egde, that u is again explorign v whcih it has already explored earlier ,
but here it cant happen because this forward edge between u and v is bidirectional that is it is from u to v and from v to u , so the first time we reached v from u , then while explrign the neighbors of v we go to this forward edge and treat it as a back edge

also there is no corss edge , see cross edge tab hoti hai , jab ham kisi ek subtree se doosre subtree ke liye ek edge ho

lets say node is the root node  and its left subtree has u and right subtree has v , now we ave already exproled the left subtree and now we are exploring the righ subtree and thter is a edge from v to u , but neigher off u or v is descendent or ancestor of each other so this is a cross edge ,

but in case of undirected if the cross edge between v and u is present it means that edge was also between u and v , so while we were exploring the left subtree of node , when we encountered u then from u we could have also gone to v , making thsi cross edge as the tree edge
*/

void dfs(int node, unordered_map<int, vector<pair<int, int>>> &adj, vector<int> &visited, vector<int> &used)
{

  visited[node] = 1;

  for (auto [it, idx] : adj[node])
  {

    if (used[idx])
      continue;
    used[idx] = 1;

    if (visited[it] == 0)
    {
      cout << node << "->" << it << " tree edge" << endl;
      dfs(it, adj, visited, used);
    }

    else
    {
      // see there is no concept of forward and cross edge so we dont' require black cases , so visited 1 and 2 are the same thing -> back edge

      cout << node << "->" << it << " back edge" << endl;
    }
  }
  visited[node] = 2;
  return;
}

void classify_edge(unordered_map<int, vector<pair<int, int>>> &adj, int v, int e)
{

  vector<int> visited(v, 0);
  vector<int> used(e, 0);

  for (int i = 0; i < v; i++)
  {
    if (!visited[i])
    {
      dfs(i, adj, visited, used);
    }
  }
}
int main()
{

  int t;
  cin >> t;

  while (t--)
  {
    int n, e;
    cin >> n >> e;

    int id = 0;
    unordered_map<int, vector<pair<int, int>>> adj;
    for (int i = 0; i < e; i++)
    {
      int u, v;
      // see hame har edge ke sath uski ek unique id bhi store karni padegi , because the edge is undirected , so it can act both as a tree edge and a back edge, but we have to consder it only one of them
      cin >> u >> v;
      adj[u].push_back({v, id});

      if (u != v)
        adj[v].push_back({u, id});

      id++;
    }

    cout << "testcase-" << t << endl;
    classify_edge(adj, n, e);
    cout << endl;
  }
  return 0;
}