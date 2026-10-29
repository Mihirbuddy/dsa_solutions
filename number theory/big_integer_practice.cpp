#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

string remove_zeros(string &s)
{

  int i = 0;
  while (i < (int)s.size() - 1 && s[i] == '0')
    i++;

  /*
  see jo size hoti hai vo unsigned hoti hai so suppose if size is 0 and we do -1 on it , it will become a substantially a very large no. , so usko range me laane ke liye we typecasted it to -1 ,
  also why are we going onlyy till n-2 , because we want to return the last character anyhow , if it is 00001 then we return 1 and if it is 00000 then we want to return 0 instead of returning a empty string */
  return s.substr(i);
}

/*
see if b>a then we return -1 ,
if a>b then 1
if both are same then 0 */

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

/*ee our assignment promised that there would be no such arithmetic which will give a negative result , so if a-b is there , its result is always >=0

but in general if there is sucha case in which a<b ,then we can swap the no. and can calculte the difference and later negate the answer*/
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

  /*
  first check whether s2 is 0 or not , to avoid division by zero error

  see earlier i wrote compare(s2,"0"), which is valid in itself , but the compare function is taking the parameters by reference , which means it can modify the original string , but we are passing "0" which is a string literal whcih cannot be changed

  there were two options to resolve this , either create a string for zero and then pass it , which we are doing

  second option was that , to make the compare function such that
  compare(const string & s1, const string & s2)-> this is a better approach , but here , we can't do this , because const restricts us to modify s1 and s2 , but inside comapre we are modifying like we are remvoing the leading zeros
  */
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

string evaluate(string expr)
{
  /*expression is given us to be a infix expression , so first we convert it into a postfix expression for evaluation purposes , see generally we can't solve infix expressions directly because in whcih order will we solve it?? , because higher precedence operator can be anywhere in the expression */

  string postfix = "";
  stack<char> st;

  int i = 0;
  int n = (int)expr.size();
  while (i < n)
  {
    char c = expr[i];
    if (c == ' ' || c == '\t' || c == '\r')
    {
      i++;
      continue;
    }

    if (isdigit(c))
    {
      string num = "";
      while (i < n && isdigit(expr[i]))
        num.push_back(expr[i++]);
      postfix += num + ' ';
      continue;
    }

    if (c == '(')
      st.push(c);
    else if (c == ')')
    {
      // pop out all the elements upto (
      while (!st.empty() && st.top() != '(')
      {
        postfix.push_back(st.top());
        postfix += ' ';
        st.pop();
      }
      if (!st.empty())
        st.pop();
    }

    else
    {
      while (!st.empty() && precedence(st.top()) >= precedence(c))
      {
        postfix.push_back(st.top());
        postfix += ' ';
        st.pop();
      }
      st.push(c);
    }
    i++;
  }

  while (!st.empty())
  {
    postfix.push_back(st.top());
    postfix += ' ';
    st.pop();
  }

  // now we have the postfix expression we will now evaluate it

  int j = 0;
  int m = (int)postfix.size();
  stack<string> st1;
  while (j < m)
  {
    char ch = postfix[j];

    if (ch == ' ')
    {
      j++;
      continue;
    }

    if (isdigit(ch))
    {
      string num = "";
      while (j < m && isdigit(postfix[j]))
      {
        num.push_back(postfix[j]);
        j++;
      }
      st1.push(remove_zeros(num));
    }

    else
    {
      char op = ch;
      string op1 = "";
      string op2 = "";
      if (!st1.empty())
      {
        op1 = st1.top();
        st1.pop();
      }
      if (!st1.empty())
      {
        op2 = st1.top();
        st1.pop();
      }
      st1.push(apply_oper(ch, op2, op1));
    }
    j++;
  }

  return st1.top();
}
int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int choice;
  cout << "enter your choice\n1.evaluate expression.\n2.compare no." << endl;

  cin >> choice;

  if (choice == 1)
  {
    string expr;
    cout << "enter expression\n";
    getline(cin >> ws, expr);
    cout << "result: " << evaluate(expr) << endl;
  }
  else
  {

    string s1;
    string s2;

    cout << "enter two no.s" << endl;
    cin >> s1 >> s2;

    int r = compare(s1, s2);

    if (r == -1)
    {
      cout << s1 << "<" << s2 << endl;
    }

    else if (r == 1)
    {
      cout << s1 << ">" << s2 << endl;
    }

    else
    {
      cout << s1 << "=" << s2 << endl;
    }
  }

  return 0;
}