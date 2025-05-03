#include <iostream>
using namespace std;

// Max Heap class
class Heap {
    int *arr;
    int capacity;
    int currentSize;

public:
    Heap(int n) {
        capacity = n;
        arr = new int[n + 1]; // 1-based indexing
        currentSize = 0;
    }

    ~Heap() {
        delete[] arr;
    }

    // Insert a new value into the heap
    void insert(int value) {
        currentSize++;
        arr[currentSize] = value;
        int i = currentSize;

        while (i > 1 && arr[i] > arr[i / 2]) {
            swap(arr[i], arr[i / 2]);
            i /= 2;
        }
    }

    // Build heap from array
    void buildHeap(int input[], int n) {
        for (int i = 0; i < n; ++i) {
            insert(input[i]);
        }
    }

    // Heapify operation (used in heap sort)
    void heapify(int i, int n) {
        int largest = i;
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= n && arr[left] > arr[largest])
            largest = left;
        if (right <= n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(largest, n);
        }
    }

    // Perform heap sort (descending)
    void heapSort() {
        // Convert to max heap
        for (int i = currentSize / 2; i >= 1; i--) {
            heapify(i, currentSize);
        }

        // Sort the heap
        for (int i = currentSize; i > 1; i--) {
            swap(arr[1], arr[i]);
            heapify(1, i - 1);
        }
    }

    void displaySorted() {
        cout << "\n# Marks in descending order:\n";
        for (int i = currentSize; i >= 1; i--) {
            cout << arr[i] << " ";
        }
        cout << "\n# Highest score: " << arr[currentSize] 
             << " & Lowest score: " << arr[1] << endl;
    }
};

// Class to handle marks input and sorting
class Marks {
    int arr[50];
    int n;

public:
    void input() {
        cout << "Enter number of students: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter marks of student " << (i + 1) << ": ";
            cin >> arr[i];
        }
    }

    void processHeap() {
        Heap maxHeap(n);
        maxHeap.buildHeap(arr, n);
        maxHeap.heapSort();
        maxHeap.displaySorted();
    }
};

int main() {
    Marks obj;
    obj.input();
    obj.processHeap();
    return 0;
}
