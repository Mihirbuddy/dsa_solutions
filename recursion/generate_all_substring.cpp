#include <iostream>

#include <set>

using namespace std;

void solve(string &s1, set<string> &st, string temp, int index, int n)
{
  if (index >= n)
  {
    if (!temp.empty())
      st.insert(temp);
    return;
  }

  solve(s1, st, temp, index + 1, n);

  temp.push_back(s1[index]);
  solve(s1, st, temp, index + 1, n);
  temp.pop_back();
}

int main()
{

  string s1;
  cin >> s1;
  int n = s1.size();

  string temp = "";
  set<string> st;

  solve(s1, st, temp, 0, n);
  int count = st.size();
  for (auto it : st)
  {
    // sort(it.begin(),it.end());
    cout << it;
    if (count > 1)
      cout << endl;

    count--;
  }
  return 0;
}