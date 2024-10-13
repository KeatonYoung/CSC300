#include "bstA.h"

int main (int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: ./a <filename>" << endl;
        return 1;
    }

    int size = 20;
    string filename = argv[1];

    BST bst(size);


    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file.\n";
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int command, data;
        iss >> command;

        switch (command) {
            case 0:
                cout << "Exiting...!\n";
                return 0;
            case 1:
                iss >> data;
                bst.insertI(data);
                cout << "Insert I: " << data << endl;
                break;
            case 2:
                iss >> data;
                bst.insertR(data);
                cout << "Inserted R: " << data << endl;
                break;
            case 3:
                iss >> data;
                if (bst.searchI(data))
                    cout << data << " found I.\n";
                else
                    cout << data << " not found I.\n";
                break;
            case 4:
                iss >> data;
                if (bst.searchR(data))
                    cout << data << " found R.\n";
                else
                    cout << data << " not found R.\n";
                break;
            case 5:
                cout << "Inorder traversal: ";
                bst.inorder();
                cout << endl;
                break;
            case 6:
                cout << "Preorder traversal: ";
                bst.preorder();
                cout << endl;
                break;
            case 7:
                cout << "Postorder traversal: ";
                bst.postorder();
                cout << endl;
                break;
            case 8:
                cout << "Binary Search Tree" << endl;
                bst.printTree(0, 0);
                cout<<endl;
                break;
            case 9:
                iss >> data;
                int height = bst.height(data);
                if (height >= 0)
                    cout << "Height of node at index " << data << " is " << height << endl;
                else
                    cout << "Node at index " << data << " does not exist." << endl;
                break;
            case 10:
                int totalNodes = bst.countNodes();
                cout << "Total number of nodes in the BST: " << totalNodes << endl;
                break;
            case 11:
                cout << "Is the BST balanced? " << bst.isBalanced() << endl;
                break;
            case 12: 
                cout << "BFS traversal: ";
                bst.BFS(); 
                break;
            default:
                cout << "Invalid command." << endl;
        }
    }

    return 0;
}