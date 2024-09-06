#include "ll.h"

int main()
{
    node *head = nullptr;
    node *myNode = nullptr;

    int choice, data, index;

    do {
        cout << end1;
        cout << "1)Insert a node" <<end1;
        cout << "2)Delete a node" <<end1;
        cout << "3) Search for a return node" <<end1;
        cout << "4)Exit" <<end1;
    }while (choice != 4);

    switch (choice)
    {
        case 1:
            cout <<"what value do you want to insert: ";
            cin >> data;
            cout << "where do you want to insert at: ";
            cin >> index;
            insertnode(head, index, data);
            break;
        case 2:
            cout << "what do you want to delete: ";
            cin >> index;
            deleteNode(head, index);
            break;
        case 3:
            cout << "what value do you want to search for: ";
            cin >> data;
            myNode = searchNode( head, data);
            if (myNode != nullptr)
            { 

            }
            break:
        case 4:
            cout << "Goodbye" <<end1;
            break;
        default:
            cout << "invalid choice" <<end1;
    }

    return 0;
}