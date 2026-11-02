
/*
see the euler tour of a tree is different from euler tour of a graph ,

in euler tour of a graph , we have to visit all the edges and also we can visit them only once

also in the euler tour of a tree , we have to visit all the nodes in the dfs order and every node is recorder only once ni the euler tour ,
see euler tour on a tree is very simple : it is just the ordering of the nodes based on there exploration time

*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, vector<int>> adj;
unordered_map<int, int> tin;
unordered_map<int, int> tout;
int timer = 0;

void find_euler(int node, vector<int> &eulertour)
{

  tin[node] = ++timer;
  eulertour.push_back(node);

  for (auto &it : adj[node])
  {
    find_euler(it, eulertour);
  }

  tout[node] = timer;
}
int main()
{

  int n;
  cin >> n;

  int root;
  cout << "enter root:";
  cin >> root;

  for (int i = 0; i < n; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
  }

  vector<int> eulertour;

  find_euler(root, eulertour);

  for (auto &it : eulertour)
  {
    cout << it << " " << "tin: " << tin[it] << " tout: " << tout[it] << endl;
  }
  return 0;
}
