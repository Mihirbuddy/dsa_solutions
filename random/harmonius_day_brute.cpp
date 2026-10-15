#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool solve(long long day)
{
  while (day % 2 == 0)
    day /= 2;

  while (day % 3 == 0)
    day /= 3;

  while (day % 5 == 0)
    day /= 5;

  return day == 1;
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