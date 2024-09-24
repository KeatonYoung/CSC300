#include "sqdll.h"



void enqueueFront(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the front
    node *newNode = new node;
    newNode->data = value;
    newNode->next = head;     // newNode points to first element in the list
    newNode->prev = nullptr;  // no prior elements befor newNode

    // If the deque is emtpty, then newNode also becomes both the head and the tail
    if (head == nullptr){
        head = tail = newNode;
    }
    else { // If not empty, just make newNode the head
        head->prev = newNode;
        head = newNode;
    }

}

void enqueueBack(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the back [modigy next and prev pointer accordingly]
    node *newNode =new node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    // Check if dequeue is empty, then newNode is both the head and the tail.
    if( head == nullptr){
        head = tail = newNode;
    }else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    // Else insert at the end

}

void dequeueFront(node *&head, node *&tail)
{
    // Check if deque is empty - nothing to dequeue
    if(head == nullptr){
        cout << "Deque is empty" <<endl;
        return;
    }
    node *dltTemp = head;
    if(head == tail){
        head = tail = nullptr;
    }else {
        head = head->next;
        head->prev = nullptr;
    }

    delete dltTemp;

    // Ajust the pointers for the new head and delete original head 

}

void dequeueBack(node *&head, node *&tail)
{
//    checking to see if deque is empty
    if (tail == nullptr){
        cout << "Deque is empty" <<endl;
        return;
    }
    node *dltTemp = tail;
    if (head == tail){
        head = tail = nullptr;
    }else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete dltTemp;

}

void displayList(node *&head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker -> next;
    }
    cout << endl;
}
