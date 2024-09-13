#include "ll.h"

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    if(index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while(walker != NULL && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next = newNode;
        }

    }
}

void deleteNode(node *&head, int index) 
{
    // Check if the list is empty and there's nothing to delete

        // if the null pointer is at head that means there is no elements, meaning empty.
        if(head == nullptr){
            cout << "List is empty, nothing to delete" << endl;
            return;
        }

    // Check if were are deleting at index 0 and handle accordingly
    if(index == 0)
    {
        // We point at the head and move to the next node, then delete the old head.
        node*dltTemp = head;
        head = head->next;

        delete dltTemp;
        return;
    }
    // Handle other index deletions
    else
    {
        // Write your code here!
        node* prev = nullptr;
        node* curr = head;
        int count = 0;

        while (curr != nullptr && count < index){
            prev = curr;
            curr = curr->next;
            count++;
        }
        if(curr==nullptr){
            cout <<"index is out of bounds" << endl;
            return;
        }
        prev->next = curr->next;
        delete curr;
    }
}

void displayList(node *&head) 
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;

}

node* searchNode(node *&head, int key) 
{
    node* walker = head;
    while(walker != nullptr && walker->data != key)
    {
        walker = walker->next;
    }
    if(walker == nullptr)
    {
        cout << key << "Not found" << endl;
        return nullptr;
    }
    else
    {
        return walker;
    }

}

void reverse(node *&head)
//storing the nodes and then reversing
//  the current no pointers and moving the 
// pointers position ahead
{
    node* prev = nullptr;
    node* current = head;
    node* next = nullptr;

while (current != nullptr){
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
}

head = prev;
}