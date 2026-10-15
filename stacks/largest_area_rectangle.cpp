#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

vector<int> prev_smaller(vector<int> &histogram, int n)
{
  stack<int> s;
  s.push(-1);

  vector<int> result(n);
  for (int i = 0; i < n; i++)
  {
    while (s.top() != -1 && histogram[i] <= histogram[s.top()])
      s.pop();
    result[i] = s.top();
    s.push(i);
  }

  return result;
}

vector<int> next_smaller(vector<int> &histogram, int n)
{
  stack<int> s;
  s.push(-1);

  vector<int> result(n);
  for (int i = n - 1; i >= 0; i--)
  {
    while (s.top() != -1 && histogram[i] <= histogram[s.top()])
      s.pop();
    result[i] = s.top();
    s.push(i);
  }

  return result;
}
int area_histogram(vector<int> &histogram, int n)
{
  vector<int> prev = prev_smaller(histogram, n);
  vector<int> next = next_smaller(histogram, n);

  int area = 0;
  for (int i = 0; i < n; i++)
  {
    int x, y;
    x = prev[i];
    y = next[i];
    if (y == -1)
      y = n;

    int width = y - x - 1;
    int height = histogram[i];
    area = max(area, width * height);
  }
  return area;
}
int find_max_area(vector<vector<char>> &matrix, int n, int m)
{

  vector<int> histogram(m, 0);

  int ans = 0;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (matrix[i][j] == '1')
      {
        histogram[j] += 1;
      }
      else
      {
        histogram[j] = 0;
      }
    }

    ans = max(ans, area_histogram(histogram, m));
  }

  return ans;
}
int main()
{
  int n, m;
  cin >> n >> m;

  vector<vector<char>> matrix(n, vector<char>(m));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> matrix[i][j];
    }
  }

  int ans = find_max_area(matrix, n, m);
  cout << ans;
  return 0;
}