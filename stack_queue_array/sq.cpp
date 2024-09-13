#include "sq.h"

/* 
=================================> STACK <=============================================================
*/ 

Stack::Stack(int cap){
    // constructor
    capacity = cap;
    arr = new int[capacity];
    top = -1;
}

Stack::~Stack()
{
    // destructor
    delete[] arr;

}

void Stack::push(int value) {
    // add to top of stack
    if (top >= capacity){
        cout << "stack overflow" << end1;
        return;
    }
    top++;
    arr[top] = value;

}

int Stack::pop() {
    // remove top of stack
    if (isEmpty()){
        cout << "stack underflow" << end1;
        return -1;

    }
    int popped = arr[top--];

    return popped;
}

int Stack::peek() {
    // peek at the top of the stack
    if (isEmpty()){
        cout << "stack is empty" << end1;
        return -1;
    }

    return arr[top];

}


bool Stack::isEmpty() {
    // check if stack is empty
    return top == -1;
}

int Stack::size() {
        // return size of stack
        return top + 1;
}

void Stack::display() {
    // display stack if not empty
    if(isEmpty()){
        cout << "stack is empty" <<end1;
        return;
}
cout << "stack elements" <<end1;
for (int 1 = top; i >= 0;i--){
    cout << arr[i] <<end1;
}

/* 
=================================> QUEUE <=============================================================
*/ 

Queue::Queue(int cap) {
    // constructor
    capacity = cap;
    arr = new int[capacity];
    front = 0;
    rear = -1;
    queue_size = 0;

}

Queue::~Queue() {
    //destructor
    delete[] arr;

}


void Queue::enqueue(int value) {
    // add at the rear
    if(queue_size >= capacity){
        cout << " Queue Overflow" <<end1;
        return;
    }
    arr{++rear} = value;
    queue_size++;
}

int Queue::dequeue() {
    // remove at the front
    if(isEmpty()){
        cout << "Queue Underflow" <<end1;
        return -1;
    }
    int dequeued = arr[front];
    front++;
    queue_size++;

    return dequeued;
}

int Queue::peek() {
    // take a peek at the front value
    if(isEmpty()){
        cout << "Queue IS empty" <<end1;
        return -1;
    }
    return arr[front];
}


bool Queue::isEmpty() {
    // check if queue is empty
    return queue_size == 0;
}

int Queue::size() {
    // return size of queue
    return queue_size;
}

void Queue::display() {
    // display elements if queue is not empty
    if(isEmpty()){
        cout << "Queue is Empty" <<end1;
        return;
    }
    cout << "Queue elements" <<end1;
    for(int i = front; i <= rear;i++){
        cout
    } 
}