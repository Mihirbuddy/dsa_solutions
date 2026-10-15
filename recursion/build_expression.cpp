#include <bits/stdc++.h>

using namespace std;

void solve(int ind, string &num, int n, long long target, long long currvalue, vector<string> &ans, string curr, long long last_operand)
{
  if (ind == n)
  {
    if(currvalue==target)
      ans.push_back(curr);
    return;
  }

  long long new_value = 0;
  for (int i = ind; i < n; i++)
  {
    if (i != ind && num[ind] == '0')
      break;
    new_value = new_value * 10 + (num[i] - '0');
    string currexpression = num.substr(ind, i - ind + 1);

    if (ind == 0)
    {
      solve(i + 1, num, n, target, new_value, ans, currexpression, new_value);
    }
    else
    {
      //+
      solve(i + 1, num, n, target, currvalue + new_value, ans, curr + '+' + currexpression, new_value);
      //-
      solve(i + 1, num, n, target, currvalue - new_value, ans, curr + '-' + currexpression, -new_value);
      //*
      long long new_value1 = currvalue - last_operand + (last_operand * new_value);
      solve(i + 1, num, n, target, new_value1, ans, curr + '*' + currexpression, last_operand * new_value);
    }
  }
}
int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cout << "enter the no. of testcases";
  cin >> t;

  while (t--)
  {
    string num;
    cout << "enter the string" << endl;
    cin >> num;

    int tar;
    cout << "enter the target" << endl;
    cin >> tar;

    vector<string> ans;

    solve(0, num, num.size(), tar, 0, ans, "", 0);

    for (int i = 0; i < ans.size(); i++)
    {
      cout << ans[i] << " ";
    }
    cout << endl;
  }

  return 0;
}