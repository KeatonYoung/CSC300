#include "sqll.h"

void push(node *&head, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // INSERT AT INDEX 0
    newNode->next = head;
    head = newNode;
}

void pop(node *&head)
{
    if(head == nullptr){
        cout << "Stack is empty, nothing to pop" << endl;
        return;
    }

    // remove the head
    node *dltTemp = head;
    head = head->next;

    delete dltTemp;

}

void enqueue(node *&head, int value) // add at the end
{
    // create new node to insert
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;
    // check it queue is empty -> new node becomes the head
    if(head == nullptr){
        head = newNode;
        head->next = head;
    } else {
        node *walker = head;
        while (walker->next != head){
            walker = walker->next;
        }
        walker->next = newNode;
        newNode->next = head;
    }
    // walker to walk to the end -> add my new node
}
void dequeue(node *&head) 
{
    // check if empty -> can't dequeue
    if(head == nullptr){
        cout << "queue is empty" <<endl;
        return;

    }
    node *dltTemp = head;
    node *lastNode = head;
    // dltTemp, make the 2nd element the new head
    while(lastNode->next != head){
        lastNode = lastNode->next;
    }
    head = head->next;
    lastNode->next = head;
    // delete head
    delete dltTemp;
}

void displayList(node *&head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}