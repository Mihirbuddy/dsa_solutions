#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;
typedef vector<int> vec;
typedef vector<ll> vecl;

void merge(vecl &a, int low, int high, int mid)
{

  vecl t(high - low + 1);
  int k = 0;
  int i = low;
  int j = mid + 1;

  while (i <= mid && j <= high)
  {

    if (a[i] <= a[j])
    {
      t[k] = a[i];
      i++;
      k++;
    }
    else
    {
      t[k] = a[j];
      j++;
      k++;
    }
  }

  while (i <= mid)
  {
    t[k] = a[i];
    i++;
    k++;
  }

  while (j <= high)
  {
    t[k] = a[j];
    j++;
    k++;
  }

  for (int k = low; k <= high; k++)
  {
    a[k] = t[k - low];
  }
}

ll count_inv(vecl &a, int low, int high, int mid, int x)
{

  ll count = 0;

  int left = low;
  int right = mid + 1;

  for (int i = low; i <= mid; i++)
  {

    while (right <= high && a[right] <= a[i] - x)
      right++;

    count = count + right - mid - 1;
  }

  return count;
}
ll mergesort(vecl &a, int x, int low, int high)
{

  if (low >= high)
  {
    return 0;
  }

  int mid = low + (high - low) / 2;

  ll count = 0;
  count += mergesort(a, x, low, mid);
  count += mergesort(a, x, mid + 1, high);
  count += count_inv(a, low, high, mid, x);
  merge(a, low, high, mid);

  return count;
}

int main()
{
  int n;
  ll x, y;

  cin >> n >> x >> y;

  vecl a(n);
  vecl b(n);

  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
  }

  for (int i = 0; i < n; i++)
  {
    a[i] = b[i] - a[i];
  }

  x = x - y;

  cout << mergesort(a, x, 0, n - 1);
  return 0;
}