#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool detect_cycle(int node, vector<vector<int>> &graphs, vector<int> &visited)
{

  visited[node] = 1;
  bool result = false;

  for (auto &it : graphs[node])
  {
    if (!visited[it])
    {
      result = result || detect_cycle(it, graphs, visited);
    }

    else if (visited[it] == 1)
    {
      return true;
      break;
    }

    else
      continue;
  }

  visited[node] = 2;
  return result;
}
bool find_cycle(vector<vector<int>> &graphs)
{
  int n = graphs.size();
  vector<int> visited(n, 0);

  for (int i = 0; i < n; i++)
  {
    if (!visited[i])
    {
      if (detect_cycle(i, graphs, visited))
        return true;
    }
  }

  return false;
}

int main()
{

  int n;
  cin >> n;
  cin.ignore();
  vector<vector<int>> graphs(n);

  for (int i = 0; i < n; i++)
  {
    string s;
    getline(cin, s);
    stringstream ss(s);
    vector<int> temp;
    int value;
    while (ss >> value)
    {
      temp.push_back(value);
    }

    graphs[i] = temp;
  }

  bool result = find_cycle(graphs);
  result ? cout << "true" : cout << "false";

  return 0;
}