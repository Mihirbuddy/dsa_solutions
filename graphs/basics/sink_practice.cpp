#include <iostream>
#include <vector>

using namespace std;

int find_sink(vector<vector<int>> &graphs)
{

  int i = 0;
  int j = 0;
  int n = graphs.size();
  while (i < n && j < n)
  {
    if (graphs[i][j] == 1)
    {
      i++;
    }
    else
    {
      j++;
    }
  }
  int sink = -1;
  if (i >= n)
  {
    sink = j;
  }
  else
  {
    sink = i;
  }

  if (sink >= n)
    return -1;

  // check the sink

  for (int i = 0; i < n; i++)
  {
    if (i != sink && graphs[i][sink] != 1)
    {
      return -1;
    }

    if (graphs[sink][i] == 1)
    {
      return -1;
    }
  }

  return sink;
}
int find_source(vector<vector<int>> &graphs)
{
  int i = 0;
  int j = 0;
  int n = graphs.size();
  while (i < n && j < n)
  {
    if (i == j)
    {
      if (graphs[i][j] == 1)
        i++;
      else
        j++;
    }
    else if (graphs[i][j] == 0)
    {
      i++;
    }
    else
    {
      j++;
    }
  }
  int source = -1;
  if (i >= n)
  {
    source = j;
  }
  else
  {
    source = i;
  }

  if (source >= n)
    return -1;

  // check the sink

  for (int i = 0; i < n; i++)
  {
    if (graphs[i][source] == 1)
    {
      return -1;
    }

    if (i != source && graphs[source][i] == 0)
    {
      return -1;
    }
  }

  return source;
}
int main()
{

  int t;
  cin >> t;

  while (t--)
  {
    int n;
    cin >> n;
    vector<vector<int>> graphs(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cin >> graphs[i][j];
      }
    }

    int sink = find_sink(graphs);
    int source = find_source(graphs);

    if (sink != -1)
    {
      cout << "universal sink is" << sink;
    }
    else
    {
      cout << "there is no universal sink";
    }
    cout << endl;
    if (source != -1)
    {
      cout << "universal source is" << source;
    }
    else
    {
      cout << "there is no universal source";
    }
    cout << endl;

    cout << endl;
  }
  return 0;
}