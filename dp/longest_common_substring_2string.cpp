#include <iostream>
#include <vector>

using namespace std;

// void findans(string &ans,vector<vector<vector<int>>> &dp,string &s1,string &s2,string &s3){

// }

int solve(int i, int j, vector<vector<int>> &dp, string &s1, string &s2, int &maxlen)
{

  if (i >= s1.length() || j >= s2.length())
    return 0;

  if (dp[i][j] != -1)
    return dp[i][j];

  int length = 0;

  if (s1[i] == s2[j])
  {
    length = 1 + solve(i + 1, j + 1, dp, s1, s2, maxlen);
    maxlen = max(maxlen, length);
  }

  solve(i + 1, j, dp, s1, s2, maxlen);
  solve(i, j + 1, dp, s1, s2, maxlen);

  return dp[i][j] = length;
}

int solvemem(string &s1, string &s2, vector<vector<int>> &dp)
{

  int n = s1.length();
  int m = s2.length();

  int max_ans = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = m - 1; j >= 0; j--)
    {
      int len = 0;
      if (s1[i] == s2[j])
      {
        len = 1 + dp[i + 1][j + 1];
      }
      dp[i][j] = len;
      max_ans = max(max_ans, len);
    }
  }

  return max_ans;
}

int main()
{

  string s1 = "";
  string s2 = "";

  cin >> s1;
  cin >> s2;

  int a = s1.length();
  int b = s2.length();

  vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

  int ans = solvemem(s1, s2, dp);

  cout << ans << endl;

  int i = 0;
  int j = 0;
  string result = "";

  while (i < a && j < b)
  {
    if (s1[i] == s2[j])
    {
      if (dp[i][j] < ans)
      {

        i++;
        j++;
      }
      else
      {
        while (ans > 0)
        {
          result += s1[i];
          i++;
          j++;
          ans--;
        }
        break;
      }
    }
    else
    {
      if (dp[i][j + 1] <= dp[i + 1][j])
      {
        i++;
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