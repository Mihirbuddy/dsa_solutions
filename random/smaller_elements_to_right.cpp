#include <iostream>
#include <vector>

using namespace std;

void merge(vector<pair<int, int>> &arr, int low, int mid, int high)
{
  int i = low;
  int j = mid + 1;
  int k = 0;

  vector<pair<int, int>> temp(high - low + 1);

  while (i <= mid && j <= high)
  {
    if (arr[i].first <= arr[j].first)
    {
      temp[k] = arr[i];
      i++;
      k++;
    }
    else
    {
      temp[k] = arr[j];
      j++;
      k++;
    }
  }

  while (i <= mid)
  {
    temp[k] = arr[i];
    i++;
    k++;
  }

  while (j <= high)
  {
    temp[k] = arr[j];
    j++;
    k++;
  }

  for (int i = low; i <= high; i++)
  {
    arr[i] = temp[i - low];
  }
}

void inversion(vector<pair<int, int>> &arr, int low, int mid, int high, vector<int> &ans)
{
  int right = mid + 1;

  for (int left = low; left <= mid; left++)
  {
    while (right <= high && arr[left].first > arr[right].first)
      right++;

    ans[arr[left].second] += right - (mid + 1);
  }

  return;
}

void mergesort(vector<pair<int, int>> &arr, int low, int high, vector<int> &ans)
{
  if (low >= high)
  {
    return;
  }

  int count = 0;

  int mid = (high + low) / 2;

  mergesort(arr, low, mid, ans);
  mergesort(arr, mid + 1, high, ans);
  inversion(arr, low, mid, high, ans);
  merge(arr, low, mid, high);
}

int main()
{
  int n;
  cin >> n;

  vector<pair<int, int>> arr(n);

  for (int i = 0; i < n; i++)
  {
    cin >> arr[i].first;
    arr[i].second = i;
  }

  vector<int> ans(n, 0);

  mergesort(arr, 0, n - 1, ans);

  for (int i = 0; i < n; i++)
    cout << ans[i] << " ";

  return 0;
}