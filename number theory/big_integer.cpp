// Simple BigInteger library (non-negative integers stored as digit strings)
// Operations: add, subtract (a >= b), multiply, divide, compare, expression evaluation.

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

// ---------- helper: remove leading zeros ("000120" -> "120", "000" -> "0") ----------
string removeZeros(string s)
{
  int i = 0;
  while (i < (int)s.size() - 1 && s[i] == '0')
    i++;
  return s.substr(i);
}

// ---------- compare: returns -1 if a<b, 0 if a==b, 1 if a>b ----------
int compare(string a, string b)
{
  a = removeZeros(a);
  b = removeZeros(b);
  if (a.size() != b.size())
    return a.size() < b.size() ? -1 : 1; // longer number is bigger
  if (a == b)
    return 0;
  return a < b ? -1 : 1; // same length: string comparison works digit by digit
}

// ---------- addition: O(n+m) ----------
string add(string a, string b)
{
  string res = "";
  int i = a.size() - 1, j = b.size() - 1, carry = 0;
  while (i >= 0 || j >= 0 || carry > 0)
  {
    int sum = carry;
    if (i >= 0)
      sum += a[i--] - '0';
    if (j >= 0)
      sum += b[j--] - '0';
    res.push_back('0' + sum % 10);
    carry = sum / 10;
  }
  reverse(res.begin(), res.end());
  return removeZeros(res);
}

// ---------- subtraction: O(n+m), requires a >= b ----------
string subtract(string a, string b)
{
  string res = "";
  int i = a.size() - 1, j = b.size() - 1, borrow = 0;
  while (i >= 0)
  {
    int d = (a[i--] - '0') - borrow;
    if (j >= 0)
      d -= (b[j--] - '0');
    if (d < 0)
    {
      d += 10;
      borrow = 1;
    }
    else
      borrow = 0;
    res.push_back('0' + d);
  }
  reverse(res.begin(), res.end());
  return removeZeros(res);
}

// ---------- multiplication: O(n*m), school method ----------
string multiply(string a, string b)
{
  int n = a.size(), m = b.size();
  string r(n + m, '0'); // result has at most n+m digits, stored as characters
  for (int i = n - 1; i >= 0; i--)
  {
    for (int j = m - 1; j >= 0; j--)
    {
      int sum = (a[i] - '0') * (b[j] - '0') + (r[i + j + 1] - '0');
      r[i + j + 1] = '0' + sum % 10;  // keep one digit here
      r[i + j] = r[i + j] + sum / 10; // push carry to the left
    }
  }
  return removeZeros(r);
}

// ---------- division (quotient only): long division ----------
// For each digit of a: remainder = remainder*10 + digit,
// then subtract b from remainder as many times as possible (max 9) -> that count is the quotient digit.
string divide(string a, string b)
{
  if (compare(b, "0") == 0)
  {
    cout << "Error: division by zero\n";
    return "0";
  }
  string quotient = "", rem = "0";
  for (char c : a)
  {
    rem = removeZeros(rem + c);
    int count = 0;
    while (compare(rem, b) >= 0)
    {
      rem = subtract(rem, b);
      count++;
    }
    quotient.push_back('0' + count);
  }
  return removeZeros(quotient);
}

// ---------- apply one operator ----------
string applyOp(string a, string b, char op)
{
  if (op == '+')
    return add(a, b);
  if (op == '-')
    return subtract(a, b); // problem guarantees a >= b
  if (op == '*')
    return multiply(a, b);
  return divide(a, b); // '/'
}

// ---------- BODMAS: precedence of operators ----------
int precedence(char op)
{
  if (op == '*' || op == '/')
    return 2;
  if (op == '+' || op == '-')
    return 1;
  return 0; // '('
}

// ---------- expression evaluation ----------
// Step 1: infix -> postfix (shunting-yard with operator stack)
// Step 2: evaluate postfix with a number stack
string evaluate(string expr)
{
  // ---- Step 1: infix to postfix; postfix is a string, tokens separated by spaces ----
  string postfix = "";
  stack<char> ops;
  int i = 0, n = expr.size();
  while (i < n)
  {
    char c = expr[i];
    if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
    {
      i++;
      continue;
    } // skip whitespace
    if (isdigit(c))
    { // read the whole number
      string num = "";
      while (i < n && isdigit(expr[i]))
        num.push_back(expr[i++]);
      postfix += num + " ";
      continue;
    }
    if (c == '(')
    {
      ops.push(c);
    }
    else if (c == ')')
    {
      while (!ops.empty() && ops.top() != '(')
      {
        postfix += ops.top();
        postfix += ' ';
        ops.pop();
      }
      if (!ops.empty())
        ops.pop(); // remove '('
    }
    else
    { // + - * /
      // pop operators of higher or equal precedence first (left associative)
      while (!ops.empty() && precedence(ops.top()) >= precedence(c))
      {
        postfix += ops.top();
        postfix += ' ';
        ops.pop();
      }
      ops.push(c);
    }
    i++;
  }
  while (!ops.empty())
  {
    postfix += ops.top();
    postfix += ' ';
    ops.pop();
  }

  // ---- Step 2: evaluate postfix (scan the string left to right) ----
  stack<string> st;
  int k = 0, len = postfix.size();
  while (k < len)
  {
    char c = postfix[k];
    if (c == ' ')
    {
      k++;
      continue;
    }
    if (isdigit(c))
    { // read a whole number, push it
      string num = "";
      while (k < len && isdigit(postfix[k]))
        num.push_back(postfix[k++]);
      st.push(removeZeros(num));
    }
    else
    { // operator
      string b = st.top();
      st.pop(); // right operand comes out first
      string a = st.top();
      st.pop();
      st.push(applyOp(a, b, c));
      k++;
    }
  }
  return st.top();
}

int main()
{
  int choice;
  cout << "1. Evaluate expression\n2. Compare two numbers\nChoice: ";
  cin >> choice;
  cin.ignore(); // skip newline

  if (choice == 1)
  {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);
    cout << "Result: " << evaluate(expr) << endl;
  }
  else
  {
    string a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    int r = compare(a, b);
    if (r < 0)
      cout << a << " < " << b << endl;
    else if (r > 0)
      cout << a << " > " << b << endl;
    else
      cout << a << " = " << b << endl;
  }
  return 0;
}