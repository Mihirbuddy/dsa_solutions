#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

void merge(int low, int high, int mid, vector<long long> &nums)
{
  vector<ll> temp(high - low + 1);

  ll l = low;
  ll h = mid + 1;
  ll k = 0;

  while (l <= mid && h <= high)
  {
    if (nums[l] >= nums[h])
    {
      temp[k] = nums[h];
      k++;
      h++;
    }

    else
    {
      temp[k] = nums[l];
      l++;
      k++;
    }
  }

  while (l <= mid)
  {
    temp[k] = nums[l];
    k++;
    l++;
  }

  while (h <= high)
  {
    temp[k] = nums[h];
    k++;
    h++;
  }

  for (int i = low; i <= high; i++)
  {
    nums[i] = temp[i - low];
  }
}

long long count_pair(int low, int high, int mid, vector<long long> &nums, vector<ll> &ans)
{

  ll right = mid + 1;
  ll count = 0;

  for (int i = low; i <= mid; i++)
  {

    while (right <= high && nums[i] > nums[right])
    {
      right++;
    }

    count += right - (mid + 1);
    ans[i] = count;
  }

  return count;
}

long long mergesort(vector<long long> &nums, int low, int high, vector<ll> &ans)
{
  if (low >= high)
  {
    return 0;
  }

  ll mid = low + (high - low) / 2;
  long long count = 0;
  count += mergesort(nums, low, mid, ans);
  count += mergesort(nums, mid + 1, high, ans);
  count += count_pair(low, high, mid, nums, ans);
  merge(low, high, mid, nums);

  return count;
}
// long long int inversionCount(vector<long long> &nums)
// {

//   int n = nums.size();
//   return mergesort(nums, 0, n - 1);
// }

int main()
{

  int n;
  cin >> n;
  vector<long long> arr(n);

  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  vector<ll> ans(n);

  mergesort(arr, 0, n - 1, ans);

  for (int i = 0; i < n; i++)
    cout << ans[i] << " ";

  return 0;
}