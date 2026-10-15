#include <iostream>
#include <vector>

using namespace std;

void solve(vector<int> &arr, int &result, int n)
{

  vector<int> prefix_sum(n + 1);
  prefix_sum[0] = 0;

  for (int i = 0; i < n; i++)
  {
    arr[i] -= 1;
    prefix_sum[i + 1] = arr[i] + prefix_sum[i];

    for (int j = 0; j <= i; j++)
    {
      if (prefix_sum[i + 1] - prefix_sum[j] == 0)
        result++;
    }
  }

  return;
}
int main()
{

  int t;
  cin >> t;
  while (t--)
  {

    int result = 0;

    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
      cin >> arr[i];
    }

    solve(arr, result, n);
    cout << result << endl;
  }

  return 0;
}