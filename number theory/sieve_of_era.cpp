#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> find_primes(int n)
{

  vector<ll> sp(n + 1);

  for (int i = 0; i <= n; i++)
  {
    sp[i] = i;
  }

  for (int i = 2; i * i <= n; i++)
  {
    if (sp[i] == i)
    {
      for (int j = i * i; j <= n; j += i)
      {
        if (sp[j] == j)
          sp[j] = i;
      }
    }
  }

  return sp;
}
int main()
{

  int n;
  cin >> n;

  // find prime no. till root n

  vector<ll> prime = find_primes(n);
  vector<ll> ans;
  while (n > 1)
  {
    int smallest = prime[n];
    n = n / smallest;
    ans.push_back(smallest);
  }

  for (auto it : ans)
  {
    cout << it << " ";
  }

  return 0;
}