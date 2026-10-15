#include <iostream>
#include <vector>

using namespace std;

// void findans(string &ans,vector<vector<vector<int>>> &dp,string &s1,string &s2,string &s3){

// }

int solve(int i, int j, int k, vector<vector<vector<int>>> &dp, string &s1, string &s2, string &s3, int &maxlen)
{

  if (i >= s1.length() || j >= s2.length() || k >= s3.length())
    return 0;

  if (dp[i][j][k] != -1)
    return dp[i][j][k];

  int length = 0;

  if (s1[i] == s2[j] && s1[i] == s3[k])
  {
    length = 1 + solve(i + 1, j + 1, k + 1, dp, s1, s2, s3, maxlen);
    maxlen = max(maxlen, length);
  }

  solve(i + 1, j, k, dp, s1, s2, s3, maxlen);
  solve(i, j + 1, k, dp, s1, s2, s3, maxlen);
  solve(i, j, k + 1, dp, s1, s2, s3, maxlen);

  return dp[i][j][k] = length;
}

int solvemem(string &s1, string &s2, string &s3, vector<vector<vector<int>>> &dp)
{

  int n = s1.length();
  int m = s2.length();
  int c = s3.length();

  int max_ans = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = m - 1; j >= 0; j--)
    {
      for (int k = c - 1; k >= 0; k--)
      {

        int len = 0;
        if (s1[i] == s2[j] && s1[i] == s3[k])
        {
          len = 1 + dp[i + 1][j + 1][k + 1];
        }
        dp[i][j][k] = len;
        max_ans = max(max_ans, len);
      }
    }
  }

  return max_ans;
}

int main()
{

  string s1 = "";
  string s2 = "";
  string s3 = "";

  cin >> s1;
  cin >> s2;
  cin >> s3;

  int a = s1.length();
  int b = s2.length();
  int c = s3.length();

  vector<vector<vector<int>>> dp(a + 1, vector<vector<int>>(b + 1, vector<int>(c + 1, 0)));

  // int maxlen = 0;
  // solve(0, 0, 0, dp, s1, s2, s3, maxlen);
  // int ans = maxlen;
  // cout << ans<<endl;

  int ans = solvemem(s1, s2, s3, dp);
  cout << ans << endl;

  int i = 0;
  int j = 0;
  int k = 0;
  string result = "";

  while (i < a && j < b && k < c)
  {
    if (s1[i] == s2[j] && s1[i] == s3[k])
    {
      if (dp[i][j][k] < ans)
      {

        i++;
        j++;
        k++;
      }
      else
      {
        while (ans > 0)
        {
          result += s1[i];
          i++;
          j++;
          k++;
          ans--;
        }
        break;
      }
    }
    else
    {
      if (dp[i][j + 1][k] <= dp[i + 1][j][k] && dp[i][j][k + 1] <= dp[i + 1][j][k])
      {
        i++;
      }
      else if (dp[i][j + 1][k] <= dp[i + 1][j][k])
      {
        k++;
      }
      else
      {
        j++;
      }
    }
  }

  cout << "this is the result" << result;

  // string ans="";
  // findans(ans,dp,s1,s2,s3);
  // cout<<ans;
  return 0;
}