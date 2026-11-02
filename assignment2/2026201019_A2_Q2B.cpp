#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int* arr;
    int count;
    int capacity;
    bool maxHeap;

    bool comesFirst(int a, int b) {
        if (maxHeap) return a > b;
        else         return a < b;
    }

    void swapValues(int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // array is full, make it twice as big
    void makeBigger() {
        int newCapacity = capacity * 2;
        int* newArr = new int[newCapacity];
        for (int i = 0; i < count; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

    void moveUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (comesFirst(arr[i], arr[parent])) {
                swapValues(i, parent);
                i = parent;
            } else {
                break;
            }
        }
    }

    void moveDown(int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int best = i;

            if (left < count && comesFirst(arr[left], arr[best])) {
                best = left;
            }
            if (right < count && comesFirst(arr[right], arr[best])) {
                best = right;
            }

            if (best == i) break;

            swapValues(i, best);
            i = best;
        }
    }

public:
    PriorityQueue(bool isMaxHeap) {
        capacity = 16;
        count = 0;
        maxHeap = isMaxHeap;
        arr = new int[capacity];
    }

    ~PriorityQueue() {
        delete[] arr;
    }

    int size() {
        return count;
    }

    bool empty() {
        return count == 0;
    }

    int top() {
        return arr[0];
    }

    void push(int value) {
        if (count == capacity) {
            makeBigger();
        }
        arr[count] = value;
        moveUp(count);
        count++;
    }

    void pop() {
        if (count == 0) return;
        arr[0] = arr[count - 1];
        count--;
        if (count > 0) {
            moveDown(0);
        }
    }
};


class OverallMedian {
private:
    PriorityQueue lowerHalf;
    PriorityQueue upperHalf;

public:
    OverallMedian() : lowerHalf(true), upperHalf(false) {}

    void addNumber(int x) {
        if (lowerHalf.empty() || x <= lowerHalf.top()) {
            lowerHalf.push(x);
        } else {
            upperHalf.push(x);
        }

        // keep the sizes balanced (lower can have at most 1 extra)
        if (lowerHalf.size() > upperHalf.size() + 1) {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
        } else if (lowerHalf.size() < upperHalf.size()) {
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
        }
    }

    int getDoubleMedian() {
        if (lowerHalf.size() > upperHalf.size()) {
            return 2 * lowerHalf.top();
        }
        return lowerHalf.top() + upperHalf.top();
    }
};


class WindowMedian {
private:
    PriorityQueue lowerHalf;
    PriorityQueue upperHalf;
    int lowerCount;
    int upperCount;
    int toDelete[100005];   
    void cleanTop(PriorityQueue &heap) {
        while (!heap.empty() && toDelete[heap.top()] > 0) {
            toDelete[heap.top()]--;
            heap.pop();
        }
    }

    // keep both halves balanced
    void balance() {
        if (lowerCount > upperCount + 1) {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
            lowerCount--;
            upperCount++;
            cleanTop(lowerHalf);
        } else if (lowerCount < upperCount) {
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
            upperCount--;
            lowerCount++;
            cleanTop(upperHalf);
        }
    }

public:
    WindowMedian() : lowerHalf(true), upperHalf(false) {
        lowerCount = 0;
        upperCount = 0;
        for (int i = 0; i < 100005; i++) {
            toDelete[i] = 0;
        }
    }

    void addNumber(int x) {
        if (lowerHalf.empty() || x <= lowerHalf.top()) {
            lowerHalf.push(x);
            lowerCount++;
        } else {
            upperHalf.push(x);
            upperCount++;
        }
        balance();
    }

    void removeNumber(int x) {
        toDelete[x]++;   // just mark it, don't remove yet

        if (x <= lowerHalf.top()) {
            lowerCount--;
        } else {
            upperCount--;
        }

        cleanTop(lowerHalf);
        cleanTop(upperHalf);
        balance();
        cleanTop(lowerHalf);
        cleanTop(upperHalf);
    }

    // returns median * 2
    int getDoubleMedian() {
        if (lowerCount > upperCount) {
            return 2 * lowerHalf.top();
        }
        return lowerHalf.top() + upperHalf.top();
    }
};

int main() {
    int n, d;
    cin >> n >> d;

    int* sales = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> sales[i];
    }

    OverallMedian overall;   // median of everything from day 1
    WindowMedian window;     // median of the last d days

   
    for (int i = 0; i < d; i++) {
        overall.addNumber(sales[i]);
        window.addNumber(sales[i]);
    }

    int freeDays = 0;

    for (int i = d; i < n; i++) {
        
        int doubleLimit = window.getDoubleMedian() + overall.getDoubleMedian();

        
        if (2 * sales[i] >= doubleLimit) {
            freeDays++;
        }

        
        overall.addNumber(sales[i]);
        window.addNumber(sales[i]);
        window.removeNumber(sales[i - d]);   // the day that fell out of the window
    }

    cout << freeDays << endl;

    delete[] sales;
    return 0;
}