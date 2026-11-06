/*
Lini ma'am has sprung another surprise slip test. This was also a surprise for the TAs

The slip test has four versions of the question paper, printed as Set a, Set b, Set c and Set d. The classroom has n seats arranged in one long row, and the rule Head TA Abhijith 🐐 keeps shouting from the front of the hall is simple: no two adjacent seats may receive the same set.

Unfortunately, one TA named Dhruv 🤡 began distributing papers before this rule was announced. Abhijith stopped Dhruv once he came to knew about this but by that time some seats may already have a paper sitting on them and some seats may still be empty.

The TAs now need to know how much room they have left to work with. Count the number of ways to place papers on the remaining empty seats so that the finished row obeys the rule. Two seatings are different if at least one seat receives a different set. The answer grows quickly, so report it modulo 1000000007.

Input Format
The first line contains a single integer n — the number of seats in the row.

The second line contains a string s of length n, consisting only of the characters a, b, c, d and ?. The i-th character describes seat i: a letter means that seat already holds that set and cannot be changed, and ? means the seat is still empty.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;
typedef vector<int> vec;
typedef vector<ll> vecl;

int main()
{
  int n;
  cin >> n;
  string s;
  cin >> s;

  const int mod = 1e9 + 7;

  vecl dp(4, 0);

  ll total = 0;

  for (int i = 0; i < 4; i++)
  {
    if (s[0] == '?')
    {
      dp[i] = 1;
    }
    else if (s[0] - 'a' == i)
    {
      dp[i] = 1;
    }

    total = (total + dp[i]) % mod;
  }

  vecl np(4, 0);
  ll newtotal = 0;

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (s[i] == '?' || s[i] - 'a' == j)
      {
        np[j] = ((total - dp[j]) % mod + mod)%mod;
        newtotal = (newtotal + np[j]) % mod;
      }
    }

    for (int j = 0; j < 4; j++)
    {
      dp[j] = np[j];
      np[j] = 0;
    }
    total = newtotal;
    newtotal = 0;
  }

  cout << total << endl;

  return 0;
}