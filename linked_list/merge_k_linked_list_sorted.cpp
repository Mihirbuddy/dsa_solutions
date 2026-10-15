#include <bits/stdc++.h>
using namespace std;

class ListNode
{

public:
  int val;
  ListNode *next;

  ListNode()
  {
    val = 0;
    next = nullptr;
  }
  ListNode(int value)
  {
    val = value;
    next = nullptr;
  }
};

class compare
{
public:
  bool operator()(ListNode *a, ListNode *b)
  {
    return a->val > b->val;
  }
};

ListNode *solve(vector<ListNode *> &lists)
{

  priority_queue<ListNode *, vector<ListNode *>, compare> pq;

  for (auto it : lists)
  {
    if (it != nullptr)
      pq.push(it);
  }

  ListNode *ans = new ListNode();
  ListNode *tail = ans;

  while (!pq.empty())
  {
    ListNode *top = pq.top();
    pq.pop();

    tail->next = top;
    tail = tail->next;

    if (top->next != nullptr)
    {
      top = top->next;
      pq.push(top);
    }
  }

  return ans->next;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  vector<ListNode *> lists;
  int n;
  cout << "how many lists\n";
  cin >> n;

  for (int i = 0; i < n; i++)
  {
    cout << "enter the size of " << i << "th list\n";
    int m;
    cin >> m;
    ListNode *head = new ListNode();
    ListNode *tail = head;

    for (int j = 0; j < m; j++)
    {
      int val;
      cin >> val;
      ListNode *node = new ListNode(val);
      tail->next = node;
      tail = tail->next;
    }

    lists.push_back(head->next);
  }

  ListNode *ans = solve(lists);

  while (ans->next != nullptr)
  {
    cout << ans->val << "->";
    ans = ans->next;
  }
  cout << ans->val;

  return 0;
}