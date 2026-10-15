#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

string find_ans(string &s1, string &s2)
{

  unordered_map<char, int> count1;
  unordered_map<char, int> count2;

  for (auto &ch : s2)
  {
    count1[ch]++;
  }

  int target = count1.size();
  // cout << "target" << target << endl;

  int i = 0;
  int j = 0;

  int min_len = -1;
  int current = 0;
  int start = -1;

  while (j < s1.size())
  {

    count2[s1[j]]++;

    if (count1.find(s1[j]) != count1.end())
    {
      if (count1[s1[j]] == count2[s1[j]])
        current++;
    }

    while (current == target && i < s1.size())
    {
      int len = j - i + 1;

      if (min_len == -1 || min_len > len)
      {
        min_len = len;
        start = i;
      }

      count2[s1[i]]--;
      if (count1.find(s1[i]) != count1.end())
      {
        if (count2[s1[i]] < count1[s1[i]])
          current--;
      }
      i++;
    }

    j++;
  }

  if (start == -1)
    return "";

  return s1.substr(start, min_len + 1);
}

int main()
{
  string s1, s2;

  cin >> s1;
  cin >> s2;

  string ans = find_ans(s1, s2);
  cout << ans;
  return 0;
}