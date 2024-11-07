#include "reserve.h"

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr; 
}


BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(reservation* node)
{
    if (root == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// reserve new landing time
bool BST::reserve(int time) 
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }
 
    insert(root, time); 
  
    return true; // no conflict - reservation successful
}

// check for landing time conflicts within 3 minutes (Use recursion)
bool BST::checkConflict(reservation* node, int time) 
{
    if(node == nullptr) {
        return false;
    }
    if(abs(node->time - time) < 3){
        return true;
    }

    if(time < node->time){
        return checkConflict(node->left, time);
    } else {
        return checkConflict(node->right, time);
    }
 
}

// insert new reservation and update subtree size (make sure to avoid inserting duplicates)
void BST::insert(reservation*& node, int time) 
{
    if(node == nullptr){
        node = new reservation(time);
        node->subtreeSize = 1;
        cout<< "Insterted" << time << "as a new node" << endl;
        return;
    }

    if (time < node->time){
        insert(node->left, time);
    } else if(time > node->time){
        insert(node->right, time);
    }else {
        return;
    }

    node->subtreeSize = 1;
    if(node->left) {
        node->subtreeSize += node->left->subtreeSize;
    }
    if(node->right){
        node->subtreeSize += node->right->subtreeSize;
    }
    cout << "Updated subtree size of node " << node->time << " to " << node->subtreeSize << endl;
    // same as before - just make sure to update subtree size for inserted node
}

// Count nodes with times <= t
int BST::countPlanes(reservation* node, int t) 
{
    if(node == nullptr){
        return 0;
    }
    if(node->time <= t){
        int left_count = (node->left) ? node->left->subtreeSize : 0;

        return 1 + left_count + countPlanes(node->right, t);
    } else {
        return countPlanes(node->left, t);
    }
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;
    
    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}