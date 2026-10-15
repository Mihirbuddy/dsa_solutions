
/*
Max of min for every window size
Submit solution
All submissions
Best submissions
Points:100
Time limit:1.0s
Memory limit:256M
Authors:
Pico, kavan.gandhi@students.iiit.ac.in, sureshkumar.vuyala@students.iiit.ac.in
Allowed languages
C++
You are given an integer array arr[].
The task is to find the maximum of minimum values for every window size k where 1 ≤ k ≤ arr.size().

Problem Description
For each window size k, consider all contiguous subarrays of length k.
Determine the minimum element in each subarray.
Then, take the maximum among all these minimums.
Return the results as an array, where the element at index i represents the answer for window size i+1.

Input Format
An integer n — the size of the array.
n space-separated integers representing the array elements.
Output Format
Print n integers — the result array.
The element at index i corresponds to the maximum of minimums for window size i+1.

Constraints
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^6


Example-1
Input:

Copy
7
10 20 30 50 10 70 30
Output:
70 30 20 10 10 10 10

Explanation:

Window size = 1 → max of minimums = 70
Window size = 2 → max of minimums = 30
Window size = 3 → max of minimums = 20
... and so on.


Example-2
Input:

Copy
3
10 20 30
Output:
30 20 10

Explanation:

Window size = 1 → max of minimums = 30
Window size = 2 → max of minimums = 20
Window size = 3 → max of minimums = 10

*/

#include <iostream>
#include <vector>
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
int main()
{

  int n;
  cin >> n;

  vector<int> arr(n);

  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  vector<int> prev = prev_smaller(arr, n);
  vector<int> next = next_smaller(arr, n);
  vector<int> range(n);

  for (int i = 0; i < n; i++)
  {
    if (next[i] == -1)
      next[i] = n;

    range[i] = next[i] - prev[i] - 1;
  }

  vector<int> ans(n + 1, 0);

  for (int i = 0; i < n; i++)
  {
    int len = range[i];

    if (arr[i] > ans[len])
    {
      ans[len] = arr[i];
    }
  }

  for (int i = n - 1; i >= 1; i--)
  {
    if (ans[i] < ans[i + 1])
      ans[i] = ans[i + 1];
  }

  for (int i = 1; i <= n; i++)
    cout<<ans[i] <<" ";

  return 0;
}