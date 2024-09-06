#ifndef LL_H
#define LL_H

#include <iostream>

using namespace std;

struct node{
    
    int data;
    struct node *next;
    // struct node *prev (for double linked list)
};

void insertnode(node *&head, int index, int data);
void deleteNode(node *&head, int index);
void displayList(node *&head);
node* searchNode(node *&head, int key);

#endif

