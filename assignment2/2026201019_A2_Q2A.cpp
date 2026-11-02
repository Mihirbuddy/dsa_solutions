#include <iostream>
using namespace std;

class priority_queue_custom
{
private:
  int *heap;
  int count;
  int capacity;

  void swapVals(int &a, int &b)
  {
    int t = a;
    a = b;
    b = t;
  }

  void grow()
  {
    int newCap = capacity * 2;
    int *newHeap = new int[newCap];
    for (int i = 0; i < count; i++)
      newHeap[i] = heap[i];
    delete[] heap;
    heap = newHeap;
    capacity = newCap;
  }

  void siftUp(int i)
  {
    while (i > 0)
    {
      int parent = (i - 1) / 2;
      if (heap[parent] < heap[i])
      { // '>' for min-heap
        swapVals(heap[parent], heap[i]);
        i = parent;
      }
      else
      {
        break;
      }
    }
  }

  void siftDown(int i)
  {
    while (true)
    {
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      int largest = i;

      if (left < count && heap[left] > heap[largest]) // '<' for min-heap
        largest = left;
      if (right < count && heap[right] > heap[largest]) // '<' for min-heap
        largest = right;

      if (largest != i)
      {
        swapVals(heap[i], heap[largest]);
        i = largest;
      }
      else
      {
        break;
      }
    }
  }

public:
  // 1. Constructor - O(1)
  priority_queue_custom()
  {
    capacity = 16;
    count = 0;
    heap = new int[capacity];
  }

  priority_queue_custom(const priority_queue_custom &other)
  {
    capacity = other.capacity;
    count = other.count;
    heap = new int[capacity];
    for (int i = 0; i < count; i++)
      heap[i] = other.heap[i];
  }

  priority_queue_custom &operator=(const priority_queue_custom &other)
  {
    if (this != &other)
    {
      delete[] heap;
      capacity = other.capacity;
      count = other.count;
      heap = new int[capacity];
      for (int i = 0; i < count; i++)
        heap[i] = other.heap[i];
    }
    return *this;
  }

  ~priority_queue_custom()
  {
    delete[] heap;
  }

  // 2. size() - O(1)
  int size()
  {
    return count;
  }

  // 3. push() - O(log n)
  void push(int el)
  {
    if (count == capacity)
      grow();
    heap[count] = el;
    siftUp(count);
    count++;
  }

  // 4. top() - O(1)
  int top()
  {
    if (count == 0)
    {
      cout << "Priority queue is empty!" << endl;
      return -1;
    }
    return heap[0];
  }

  // 5. pop() - O(log n)
  void pop()
  {
    if (count == 0)
    {
      cout << "Priority queue is empty!" << endl;
      return;
    }
    heap[0] = heap[count - 1];
    count--;
    if (count > 0)
      siftDown(0);
  }

  // 6. empty() - O(1)
  bool empty()
  {
    return count == 0;
  }
};

int main()
{
  priority_queue_custom pq;
  int choice;

  do
  {
    cout << "\n----- Priority Queue Menu -----\n";
    cout << "1. Push\n";
    cout << "2. Pop\n";
    cout << "3. Top\n";
    cout << "4. Size\n";
    cout << "5. Empty?\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      int el;
      cout << "Enter element to push: ";
      cin >> el;
      pq.push(el);
      cout << el << " inserted." << endl;
      break;
    }
    case 2:
      if (pq.empty())
        cout << "Priority queue is empty!" << endl;
      else
      {
        cout << "Popped: " << pq.top() << endl;
        pq.pop();
      }
      break;
    case 3:
      if (pq.empty())
        cout << "Priority queue is empty!" << endl;
      else
        cout << "Top element: " << pq.top() << endl;
      break;
    case 4:
      cout << "Size: " << pq.size() << endl;
      break;
    case 5:
      cout << (pq.empty() ? "Queue is empty" : "Queue is not empty") << endl;
      break;
    case 0:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice, try again." << endl;
    }
  } while (choice != 0);

  return 0;
}