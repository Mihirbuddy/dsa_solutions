#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool find(vector<vector<int>> &graph, int node, vector<int> &visited, int color)
{

  visited[node] = color;

  for (auto &it : graph[node])
  {
    if (!visited[it])
    {
      if (!find(graph, it, visited, !color))
        return false;
    }
    else if (visited[it] == color)
    {
      return false;
    }
  }

  return true;
}
bool is_bipartite(vector<vector<int>> &graph)
{

  int n = graph.size();
  vector<int> visited(n, 0);

  for (int i = 0; i < n; i++)
  {
    if (!visited[i])
    {
      if (!find(graph, i, visited, 0))
      {
        return false;
      }
    }
  }

  return true;
}
int main()
{
  int n;
  cin >> n;
  cin.ignore();
  vector<vector<int>> graph(n);

  for (int i = 0; i < n; i++)
  {
    vector<int> temp;
    string s;
    getline(cin, s);
    stringstream ss(s);
    int value;
    while (ss >> value)
    {
      temp.push_back(value);
    }

    graph[i] = temp;
  }

  bool result = is_bipartite(graph);
  result ? cout << "true" : cout << "false";
  return 0;
}