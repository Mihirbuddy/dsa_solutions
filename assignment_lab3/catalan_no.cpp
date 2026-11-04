#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

char ch1 = '+';
char ch2 = '-';
char ch3 = '*';
char ch4 = '/';

string remove_zeros(string &s)
{

  int i = 0;
  while (i < (int)s.size() - 1 && s[i] == '0')
    i++;

  return s.substr(i);
}

int compare(string &a, string &b)
{
  a = remove_zeros(a);
  b = remove_zeros(b);

  // this function is meant to return which no. is bigger
  // if their size is different then the one with greater size would be bigger mathematically also
  if (a.size() != b.size())
    return a.size() < b.size() ? -1 : 1;
  if (a == b)
    return 0;

  return a < b ? -1 : 1;
}

string add(string &s1, string &s2)
{
  string result = "";
  int carry = 0;

  s1 = remove_zeros(s1);
  s2 = remove_zeros(s2);

  int i = (int)s1.size() - 1;
  int j = (int)s2.size() - 1;

  while (i >= 0 || j >= 0 || carry > 0)
  {
    int sum = carry;
    if (i >= 0)
      sum += s1[i--] - '0';
    if (j >= 0)
      sum += s2[j--] - '0';

    result.push_back((sum % 10) + '0');
    carry = sum / 10;
  }

  reverse(result.begin(), result.end());

  return remove_zeros(result);
}

string subtract(string &s1, string &s2)
{
  s1 = remove_zeros(s1);
  s2 = remove_zeros(s2);

  string result = "";
  int i = (int)s1.size() - 1, j = (int)s2.size() - 1, borrow = 0;

  while (i >= 0)
  {
    int diff = s1[i--] - '0' - borrow;
    if (j >= 0)
      diff -= s2[j--] - '0';

    if (diff < 0)
    {
      diff += 10;
      borrow = 1;
    }
    else
      borrow = 0;
    result.push_back(diff + '0');
  }

  reverse(result.begin(), result.end());

  return remove_zeros(result);
}

string multiply(string &s1, string &s2)
{

  int n = (int)s1.size(), m = s2.size();
  string s(n + m, '0');

  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = m - 1; j >= 0; j--)
    {
      int prod = (s1[i] - '0') * (s2[j] - '0') + (s[i + j + 1] - '0');
      s[i + j + 1] = prod % 10 + '0';
      s[i + j] += prod / 10;
    }
  }

  return remove_zeros(s);
}

string divide(string &s1, string &s2)
{

  string zero = "0";

  if (compare(s2, zero) == 0)
  {
    cout << "division by zero error" << endl;
    return "0";
  }

  string quotient = "", rem = "";

  for (char c : s1)
  {
    rem += c;
    remove_zeros(rem);
    int count = 0;
    while (compare(rem, s2) >= 0)
    {
      rem = subtract(rem, s2);
      count++;
    }
    quotient.push_back(count + '0');
  }

  return remove_zeros(quotient);
}

int precedence(char ch)
{
  if (ch == '/' || ch == '*')
    return 2;
  else if (ch == '+' || ch == '-')
    return 1;
  else
    return 0;
}

string apply_oper(char ch, string op1, string op2)
{
  if (ch == '*')
  {
    return multiply(op1, op2);
  }

  if (ch == '/')
  {
    return divide(op1, op2);
  }
  if (ch == '+')
  {
    return add(op1, op2);
  }
  if (ch == '-')
  {
    return subtract(op1, op2);
  }

  return "0";
}

string find_catalan(string s1)
{
  // 2n! +-*/

  s1 = remove_zeros(s1);
  string temp1 = "1";
  string temp2 = "2";
  string num = "1";
  string limit = apply_oper(ch3, s1, temp2);

  while (compare(temp2, limit) <= 0)
  {
    num = apply_oper(ch3, num, temp2);
    temp2 = apply_oper(ch1, temp2, temp1);
  }

  temp2 = "2";
  string den = "1";
  while (compare(temp2, s1) <= 0)
  {
    den = apply_oper(ch3, den, temp2);
    temp2 = apply_oper(ch1, temp2, temp1);
  }

  string temp3 = apply_oper(ch1, s1, temp1);
  string nplus1 = apply_oper(ch3, den, temp3);

  den = apply_oper(ch3, den, nplus1);

  string result = apply_oper(ch4, num, den);

  return remove_zeros(result);
}

int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string num;
  cin >> num;

  cout << find_catalan(num) << endl;

  return 0;
}