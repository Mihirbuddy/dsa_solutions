#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;

  ListNode(int value)
  {
    val = value;
    next = nullptr;
  }
};

void printll(ListNode *head)
{

  if (!head)
    return;

  while (head->next)
  {
    cout << head->val << "->";
    head = head->next;
  }
  cout << head->val;

  return;
}

void detect_cycle(ListNode *head)
{

  if (!head || !head->next)
  {
    cout << "cycle is not present in the list" << endl;
    return;
  }

  ListNode *slow = head;
  ListNode *fast = head;

  while (fast->next && fast->next->next)
  {
    fast = fast->next->next;
    slow = slow->next;

    if (fast == slow)
    {
      cout << "cycle is present in the list" << endl;

      slow = head;
      while (slow != fast)
      {
        slow = slow->next;
        fast = fast->next;
      }
      if (slow == fast)
      {
        cout << "the head of the cycle is" << slow->val << endl;
      }
      return;
    }
  }
  cout << "no cycle present" << endl;
  return;
}
int main()
{

  //  METHOD-1: TAKING THE WHOLE LINE AS AN INPUT LIKE : 2 3 4 5 6 7 , EOF TELLS US THAT LIST HAS ENDED
  // string line;

  // getline(cin, line);

  // stringstream ss(line);
  // see string string space separate read karta hai , aur jo bhi read karta hai usko text form me rakhta hai , then ham jis bhi data type me vo text le3te hai usi me convert ho jata hai ,
  // like value was of type int and we did ss>> value , so hamne ss ki value ko int datatype me read kiya to ss ne automatically uss type ko int bana diya.

  // ListNode *head = nullptr;
  // ListNode *tail = nullptr;

  // int value;
  // while (ss >> value)
  // {
  //   ListNode *node = new ListNode(value);

  //   if (head == nullptr)
  //   {
  //     head = node;
  //     tail = node;
  //   }
  //   else
  //   {
  //     tail->next = node;
  //     tail = tail->next;
  //   }
  // }

  // METHOD-2: TREATING -1 AS END OF INPUT
  // ListNode *head = nullptr;
  // ListNode *tail = nullptr;

  // int value;
  // while (cin >> value && value != -1)
  // {
  //   ListNode *node = new ListNode(value);

  //   if (head == nullptr)
  //   {
  //     head = node;
  //     tail = node;
  //   }
  //   else
  //   {
  //     tail->next = node;
  //     tail = tail->next;
  //   }
  // }

  // METHOD-3 TAKING NO. OF NODES AS INPUT THEN TAKING VALUES UPTO THAT NO.

  cout << "enter the no. of nodes to be entered in ll" << endl;
  int n;
  cin >> n;

  ListNode *head = nullptr;
  ListNode *tail = nullptr;

  for (int i = 0; i < n; i++)
  {
    int value;
    cin >> value;

    ListNode *node = new ListNode(value);

    if (head == nullptr)
    {
      head = node;
      tail = node;
    }

    else
    {
      tail->next = node;
      tail = tail->next;
    }
  }

  int pos;
  cout << "enter the position for the cycle(-1 for no cycle)" << endl;
  cin >> pos;
  if (pos != -1 && pos >= 0 && pos < n)
  {

    ListNode *cyclehead = head;

    for (int i = 0; i < pos; i++)
    {
      cyclehead = cyclehead->next;
    }

    tail->next = cyclehead;
  }
  else if (pos != -1)
    cout << "invalid pos" << endl;

  // printll(head);

  detect_cycle(head);

  return 0;
}