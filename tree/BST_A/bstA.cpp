#include "bstA.h"

BST:: BST(int size)
{
    capacity = size;
    tree = new int[size];
    for (int i = 0; i < size; i++)
    {
        tree[i] = INT_MIN;
    }
}
BST:: ~BST()
{
    delete[] tree;
}


int BST::leftChild(int index)
{
    return 2 * index + 1;
}
int BST::rightChild(int index)
{
    return 2 * index + 2;
}
int BST::parent(int index)
{
    return (index - 1) / 2;
}


void BST:: insertI(int data)
{
    if (tree[0] == INT_MIN) {
        tree[0] = data;
        return;
    }
    int index = 0;
    while (index < capacity){
        if (data < tree[index]) {
            if (leftChild(index) < capacity && tree[leftChild(index)] == INT_MIN) {
                tree[leftChild(index)] = data;
                return;
            }
            index = leftChild(index);
        } else {
            return;
        } if( data > tree[index]){
            if (rightChild(index) < capacity && tree[rightChild(index)] == INT_MIN) {
                tree[rightChild(index)] = data;
                return;
            }    
            index = rightChild(index);        

        } else{

            return;
        }
    }
}
void BST:: insertR(int data)
{
    insertRhelper(0, data);
}
void BST:: insertRhelper(int index, int data)
{
    if (index >= capacity)
        return;
    if (tree[index] == INT_MIN) {
        tree[index] = data;
        return;
    }

    if (data < tree[index])
        insertRhelper(leftChild(index), data);
    else if (data > tree[index])
        insertRhelper(rightChild(index), data);
    else
        return;
}


bool BST:: searchI(int data)
{
    int index = 0;
    while (index < capacity) {
        if (tree[index] == INT_MIN)
            return false;
        if (tree[index] == data)
            return true;
        if (data < tree[index])
            index = leftChild(index);
        else
            index = rightChild(index);
    }
    return false;

}
bool BST:: searchR(int data)
{
    return searchRhelper(0, data);
}
bool BST:: searchRhelper(int index, int data)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return false;
    if (tree[index] == data)
        return true;
    if (data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

void BST::preorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}
void BST::inorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));    
}
void BST::postorder(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    postorder(leftChild(index));
    postorder(rightChild(index)); 
    cout << tree[index] << " ";
}

void BST::printTree(int index, int depth = 0) {
    if (index >= capacity || tree[index] == INT_MIN) {
        return; 
    }

    printTree(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "    "; // For Indentation
    }
    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
}
int BST::height(int index){
    if (index >= capacity || tree[index] == INT_MIN){
        return -1;
    }

    int leftHeight = height(leftChild(index));
    int rightHeight = height(rightChild(index));

    return 1 + std::max(leftHeight, rightHeight);
}
int BST::countNodes(int index){
    if (index >= capacity || tree[index] == INT_MIN){
        return 0;
    }
    return 1 + leftChild(index) + rightChild(index);
}
string BST::isBalanced (){
    bool balanced = true;
    int height = isBalancedHelper(0, balanced);

    if(!balanced){
        int leftHeight = height(leftChild(0));
        int rightHeight = height(rightChild(0));
        return (leftHeight > rightHeight) ? "left-heavy" : "right-heavy";

    }
    return "yes";
}
int BST::isBalancedHelper(int index, bool &isBalanced){
    if (index >= capacity || tree[index] == INT_MIN) {
        return 0; 
    }

    int leftHeight = isBalancedHelper(leftChild(index), isBalanced);
    int rightHeight = isBalancedHelper(rightChild(index), isBalanced);
    
    if (abs(leftHeight - rightHeight) > 1) {
        isBalanced = false;
    }

    return 1 + std::max(leftHeight, rightHeight);
}
void BST::BST(){
     std::queue<int> q; 
    if (tree[0] == INT_MIN) {
        std::cout << "The tree is empty." << std::endl;
        return;
    }

    q.push(0); 

    while (!q.empty()) {
        int index = q.front(); 
        q.pop(); 

        if (index < capacity && tree[index] != INT_MIN) {
            std::cout << tree[index] << " "; 

            
            if (leftChild(index) < capacity) {
                q.push(leftChild(index));
            }

            if (rightChild(index) < capacity) {
                q.push(rightChild(index));
            }
        }
    }
    std::cout << std::endl;
}