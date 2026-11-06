#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{

  int n, q;

  cin >> n >> q;

  int row = n + 1;
  int col = 32;

  vector<vector<int>> dp(row, vector<int>(col, -1));

  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    dp[i + 1][0] = x;
  }

  for (int j = 1; j < col; j++)
  {
    for (int i = 1; i <= n; i++)
    {
      if (dp[i][j - 1] != -1)
        dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
  }

  for (int i = 0; i < q; i++)
  {
    int a, k;
    cin >> a >> k;

    for (int j = col - 1; j >= 0; j--)
    {
      if (k & (1 << j))
      {
        if (a != -1)
          a = dp[a][j];
      }
    }

    cout << a << endl;
  }

  return 0;
}