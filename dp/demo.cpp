#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool solve(long long day)
{
  if (day == 1)
    return true;

  bool flag = false;

  if (day % 2 == 1 && day % 3 != 0 && day % 5 != 0)
    return false;

  if (day % 2 == 0)
    flag = solve(day / 2);

  if (day % 3 == 0)
    flag = solve(day / 3);

  if (day % 5 == 0)
    flag = solve(day / 5);

  return flag;
}

int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;

  if (n == 1)
  {
    cout << 1;
  }

  else
  {
    long long day = 1;
    n -= 1;

    while (n)
    {
      day++;
      if (solve(day))
      {
        n -= 1;
      }
    }

    cout << day << endl;
  }
  return 0;
}