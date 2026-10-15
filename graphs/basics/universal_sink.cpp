#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<vector<int>> adj(n, vector<int>(n, 0));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> adj[i][j];
    }
  }

  int i = 0;
  int j = 0;

  while (i < n && j < n)
  {
    if (adj[i][j] == 1)
    {
      i++;
    }
    else
    {
      j++;
    }
  }

  int candidate = -1;

  if (i >= n)
    candidate = j;
  else
    candidate = i;

  if (candidate >= n)
  {
    candidate = -1;
  }

  if (candidate != -1)
  {
    // checking candidate's row and column
    for (int i = 0; i < n; i++)
    {
      if (adj[candidate][i] == 1)
      {
        candidate = -1;
        break;
      }
    }
    for (int i = 0; i < n; i++)
    {
      if (i != candidate && adj[i][candidate] == 0)
      {
        candidate = -1;
        break;
      }
    }
  }

  if (candidate == -1)
  {
    cout << "no universal sink is present" << endl;
  }
  else
  {
    cout << "universal sink is " << candidate << endl;
  }
  return 0;
}