#include "heap.h"

HEAP::HEAP(int size) {
    capacity = size;
    heapSize = 0;
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2*index + 1;
}
int HEAP::rightChild(int index) {
    return 2*index + 2;
}
int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert"<< endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while(index != 0 && array[parent(index)] < array[index]) {
        swap(array[parent(index)], array[index]);
        index = parent(index);
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    array[0] = array[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete"  << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    heapifyDown(index);
}


void HEAP::heapifyDown(int index) 
{
    // complete this
    int size = heapSize;
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < size && array[left] > array[largest]){
        largest = left;
    }
    if(right < size && array[right] > array[largest]){
        largest = right;
    }

    if (largest != index){
        std::swap(array[index], array[largest]);
        heapifyDown(largest);
    }

}

 
void HEAP::buildH(int arr[], int n) 
{
    // complete this
    int size = heapSize;
    for(int i = (size / 2) - 1; i >= 0; i--){
        heapifyDown(i);
    }
}

void HEAP::replace(int oldData, int newData)
{
    // complete this
    int index = -1;
    for(int i = 0; i < heapSize; i++){
        if(array[i] == oldData){
            index = 1;
            break;
        }
    }
    
    if( index == -1){
        return;
    }
    array[index] = newData;

    if(newData > oldData){
        heapifyUp(index);
    }else if ( newData < oldData){
        heapifyDown(index);
    }
}

void HEAP::heapSort(int arr[], int n)
{
    // complete this
    buildH(arr, n);

    int size = n;

    for(int i = size - 1; i > 0; i--){
        std::swap(array[0], array[i]);
        size--;
        heapifyDown(0);
    }
}

void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; // indentation based on depth
    }

    cout << array[index] << endl;

    printHeap(leftChild(index), depth + 1);
}

void HEAP::heapifyDownMin(int index) {
    int size = heapSize;
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && array[left] < array[smallest])
        smallest = left;

    if (right < size && array[right] < array[smallest])
        smallest = right;

    if (smallest != index) {
        std::swap(array[index], array[smallest]);
        heapifyDownMin(smallest);
    }
}
void HEAP::switchMinMax() {
    int size = heapSize;
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

