#include <bits/stdc++.h>
using namespace std;

// Move an element downward to maintain max heap
void heapify(vector<int>& heap, int n, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] > heap[largest]) {
        largest = left;
    }

    if (right < n && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapify(heap, n, largest);
    }
}

// Convert an array into a max heap
void buildHeap(vector<int>& heap) {

    int n = heap.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

// Insert a new element
void insert(vector<int>& heap, int value) {

    heap.push_back(value);

    int i = heap.size() - 1;

    while (i > 0) {

        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i]) {
            break;
        }

        swap(heap[parent], heap[i]);
        i = parent;
    }
}

// Delete maximum/root element
void deleteMax(vector<int>& heap) {

    if (heap.empty()) {
        return;
    }

    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapify(heap, heap.size(), 0);
    }
}

// Sort array in ascending order
void heapSort(vector<int>& arr) {

    buildHeap(arr);

    for (int i = arr.size() - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main() {

    vector<int> heap = {10, 30, 20, 50, 40};

    buildHeap(heap);

    insert(heap, 60);

    deleteMax(heap);

    for (int x : heap) {
        cout << x << " ";
    }

    cout << '\n';

    vector<int> arr = {40, 10, 50, 20, 30};

    heapSort(arr);

    for (int x : arr) {
        cout << x << " ";
    }

    return 0;
}