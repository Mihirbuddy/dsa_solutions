#include <bits/stdc++.h>

using namespace std;

static bool compare(const vector<int> &a, const vector<int> &b)
{
  return a[0] < b[0];
}
int solve(vector<vector<int>> &intervals)
{

  sort(intervals.begin(), intervals.end(), compare);

  int lastused = 0;

  int n = intervals.size();
  int count = 0;

  int i = 1;
  while (i < n)
  {
    if (intervals[lastused][1] <= intervals[i][0])
      lastused = i;

    else
    {
      count += 1;

      if (intervals[lastused][1] > intervals[i][1])
      {
        // better to remove lastused
        lastused = i;
      }
    }
    i++;
  }
  return count;
}

int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cin >> t;

  while (t--)
  {
    int n;
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));

    for (int i = 0; i < n; i++)
    {
      cin >> intervals[i][0] >> intervals[i][1];
    }

    int result = solve(intervals);

    cout << "result" << result << endl;
  }
  return 0;
}