#include "ll.h"

void insertnode(node *&head, int index, int data);
{
    node* newNode = new node;
    newNode->data = data;
    neNode->next = nullptr;

    if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while (walker != NULL && wIndex < index -1)
        (
            walker = walker->next;
            wIndex++;
        )
        if (walker ==nullptr)
        {
            cout << "Index is too large, cant insert."<< end1;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next neNode;
        }
    }
}
void deleteNode(node *&head, int index);
{

}
void displayList(node *&head);
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << end1;
}
node* searchNode(node *&head, int key);
{
    node* walker = head;
    while (walker != nullptr && walker->data != key)
    {
        walker = walker->next;
    }
    if (walker == nullptr)
    {
        cout << key << "Not Found" << end1;
        return nullptr;
    }
    else
    {
        return walker;
    }
}
