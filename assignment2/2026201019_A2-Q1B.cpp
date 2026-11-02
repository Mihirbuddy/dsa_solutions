#include <iostream>
using namespace std;

class Complex
{
private:
  double x = 0.0;
  double y = 0.0;

public:
  friend ostream &operator<<(ostream &output, const Complex &D)
  {
    output << D.x << "i + " << D.y << "j";
    return output;
  }
  friend istream &operator>>(istream &input, Complex &D)
  {
    input >> D.x >> D.y;
    return input;
  }
};

template <class T>
class Deque
{
private:
  T *arr;
  int capacityValue;
  int sizeValue;

  int front;
  int rear;

  void grow()
  {
    int newCapacity;

    if (capacityValue == 0)
      newCapacity = 1;
    else
      newCapacity = capacityValue * 2;

    T *newArr = new T[newCapacity];

    for (int i = 0; i < sizeValue; i++)
    {
      int index = (front + i) % capacityValue;
      newArr[i] = arr[index];
    }

    delete[] arr;

    arr = newArr;
    capacityValue = newCapacity;

    front = 0;
    rear = sizeValue - 1;
  }

  void makeCapacity(int n)
  {
    if (n <= capacityValue)
      return;

    T *newArr = new T[n];

    for (int i = 0; i < sizeValue; i++)
    {
      int index = (front + i) % capacityValue;
      newArr[i] = arr[index];
    }

    delete[] arr;

    arr = newArr;
    capacityValue = n;

    front = 0;
    rear = sizeValue - 1;
  }

public:
  Deque()
  {
    arr = nullptr;

    capacityValue = 0;
    sizeValue = 0;

    front = -1;
    rear = -1;
  }

  Deque(int n)
  {
    arr = nullptr;

    capacityValue = 0;
    sizeValue = 0;

    front = -1;
    rear = -1;

    if (n <= 0)
      return;

    arr = new T[n];

    capacityValue = n;
    sizeValue = n;

    front = 0;
    rear = n - 1;
  }

  Deque(int n, T x)
  {
    arr = nullptr;

    capacityValue = 0;
    sizeValue = 0;

    front = -1;
    rear = -1;

    if (n <= 0)
      return;

    arr = new T[n];

    capacityValue = n;
    sizeValue = n;

    front = 0;
    rear = n - 1;

    for (int i = 0; i < n; i++)
    {
      arr[i] = x;
    }
  }

  Deque(const Deque &other)
  {
    arr = nullptr;
    capacityValue = 0;
    sizeValue = 0;
    front = -1;
    rear = -1;

    if (other.capacityValue > 0)
    {
      arr = new T[other.capacityValue];
      capacityValue = other.capacityValue;
      sizeValue = other.sizeValue;

      for (int i = 0; i < sizeValue; i++)
      {
        arr[i] = other.arr[(other.front + i) % other.capacityValue];
      }

      if (sizeValue > 0)
      {
        front = 0;
        rear = sizeValue - 1;
      }
    }
  }

  Deque &operator=(const Deque &other)
  {
    if (this == &other)
      return *this;

    delete[] arr;

    arr = nullptr;
    capacityValue = 0;
    sizeValue = 0;
    front = -1;
    rear = -1;

    if (other.capacityValue > 0)
    {
      arr = new T[other.capacityValue];
      capacityValue = other.capacityValue;
      sizeValue = other.sizeValue;

      for (int i = 0; i < sizeValue; i++)
      {
        arr[i] = other.arr[(other.front + i) % other.capacityValue];
      }

      if (sizeValue > 0)
      {
        front = 0;
        rear = sizeValue - 1;
      }
    }

    return *this;
  }

  ~Deque()
  {
    delete[] arr;
  }

  void initialize()
  {
    delete[] arr;

    arr = nullptr;

    capacityValue = 0;
    sizeValue = 0;

    front = -1;
    rear = -1;
  }

  bool push_back(T x)
  {
    if (sizeValue == capacityValue)
    {
      grow();
    }

    if (sizeValue == 0)
    {
      front = 0;
      rear = 0;

      arr[rear] = x;

      sizeValue++;

      return true;
    }

    rear = (rear + 1) % capacityValue;

    arr[rear] = x;

    sizeValue++;

    return true;
  }

  bool pop_back()
  {
    if (sizeValue == 0)
      return false;

    if (sizeValue == 1)
    {
      front = -1;
      rear = -1;
      sizeValue = 0;

      return true;
    }

    rear--;

    if (rear < 0)
      rear = capacityValue - 1;

    sizeValue--;

    return true;
  }

  bool push_front(T x)
  {
    if (sizeValue == capacityValue)
    {
      grow();
    }

    if (sizeValue == 0)
    {
      front = 0;
      rear = 0;

      arr[front] = x;

      sizeValue++;

      return true;
    }

    front--;

    if (front < 0)
      front = capacityValue - 1;

    arr[front] = x;

    sizeValue++;

    return true;
  }

  bool pop_front()
  {
    if (sizeValue == 0)
      return false;

    if (sizeValue == 1)
    {
      front = -1;
      rear = -1;
      sizeValue = 0;

      return true;
    }

    front = (front + 1) % capacityValue;

    sizeValue--;

    return true;
  }

  T frontValue()
  {
    if (sizeValue == 0)
      return T();

    return arr[front];
  }

  T back()
  {
    if (sizeValue == 0)
      return T();

    return arr[rear];
  }

  T operator[](int index)
  {
    if (index >= 0)
    {
      if (index >= sizeValue)
        return T();

      int physicalIndex = (front + index) % capacityValue;

      return arr[physicalIndex];
    }

    int actualIndex = sizeValue + index;

    if (actualIndex < 0)
      return T();

    int physicalIndex = (front + actualIndex) % capacityValue;

    return arr[physicalIndex];
  }

  bool empty()
  {
    return sizeValue == 0;
  }

  int size()
  {
    return sizeValue;
  }

  void resize(int n)
  {
    if (n < 0)
      return;

    if (n < sizeValue)
    {
      if (n == 0)
      {
        front = -1;
        rear = -1;
        sizeValue = 0;

        return;
      }

      sizeValue = n;
      rear = (front + sizeValue - 1) % capacityValue;

      return;
    }

    if (n == sizeValue)
      return;

    makeCapacity(n);

    if (sizeValue == 0)
    {
      front = 0;
      rear = -1;
    }

    while (sizeValue < n)
    {
      rear = (rear + 1) % capacityValue;
      arr[rear] = T();
      sizeValue++;
    }
  }

  void resize(int n, T d)
  {
    if (n < 0)
      return;

    if (n < sizeValue)
    {
      if (n == 0)
      {
        front = -1;
        rear = -1;
        sizeValue = 0;

        return;
      }

      sizeValue = n;
      rear = (front + sizeValue - 1) % capacityValue;

      return;
    }

    if (n == sizeValue)
      return;

    makeCapacity(n);

    if (sizeValue == 0)
    {
      front = 0;
      rear = -1;
    }

    while (sizeValue < n)
    {
      rear = (rear + 1) % capacityValue;
      arr[rear] = d;
      sizeValue++;
    }
  }

  void reserve(int n)
  {
    if (n > capacityValue)
    {
      makeCapacity(n);
    }
  }

  void shrink_to_fit()
  {
    if (capacityValue == sizeValue)
      return;

    if (sizeValue == 0)
    {
      delete[] arr;

      arr = nullptr;

      capacityValue = 0;

      front = -1;
      rear = -1;

      return;
    }

    T *newArr = new T[sizeValue];

    for (int i = 0; i < sizeValue; i++)
    {
      int index = (front + i) % capacityValue;
      newArr[i] = arr[index];
    }

    delete[] arr;

    arr = newArr;

    capacityValue = sizeValue;

    front = 0;
    rear = sizeValue - 1;
  }

  void clear()
  {
    sizeValue = 0;

    front = -1;
    rear = -1;
  }

  int capacity()
  {
    return capacityValue;
  }
};

int main()
{
  Deque<Complex> dq;

  int choice;

  while (cin >> choice)
  {
    if (choice == 0)
    {
      return 0;
    }

    else if (choice == 1)
    {
      dq.initialize();
    }

    else if (choice == 2)
    {
      int n;
      cin >> n;

      dq = Deque<Complex>(n);
    }

    else if (choice == 3)
    {
      int n;
      Complex x;

      cin >> n >> x;

      dq = Deque<Complex>(n, x);
    }

    else if (choice == 4)
    {
      Complex x;
      cin >> x;

      cout << boolalpha << dq.push_back(x) << endl;
    }

    else if (choice == 5)
    {
      cout << boolalpha << dq.pop_back() << endl;
    }

    else if (choice == 6)
    {
      Complex x;
      cin >> x;

      cout << boolalpha << dq.push_front(x) << endl;
    }

    else if (choice == 7)
    {
      cout << boolalpha << dq.pop_front() << endl;
    }

    else if (choice == 8)
    {
      cout << dq.frontValue() << endl;
    }

    else if (choice == 9)
    {
      cout << dq.back() << endl;
    }

    else if (choice == 10)
    {
      int n;
      cin >> n;

      cout << dq[n] << endl;
    }

    else if (choice == 11)
    {
      cout << boolalpha << dq.empty() << endl;
    }

    else if (choice == 12)
    {
      cout << dq.size() << endl;
    }

    else if (choice == 13)
    {
      int n;
      cin >> n;

      dq.resize(n);
    }

    else if (choice == 14)
    {
      int n;
      Complex d;

      cin >> n >> d;

      dq.resize(n, d);
    }

    else if (choice == 15)
    {
      int n;
      cin >> n;

      dq.reserve(n);
    }

    else if (choice == 16)
    {
      dq.shrink_to_fit();
    }

    else if (choice == 17)
    {
      dq.clear();
    }

    else if (choice == 18)
    {
      cout << dq.capacity() << endl;
    }
  }

  return 0;
}

