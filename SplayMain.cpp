/******************************************************
*										              *
*                CE-223 Final Project:                *
*		      Splay Tree Implementation 		      *
*													  *
*		Jett Fuller, Gavin Wakefield, Luke Bray		  *
*												      *
******************************************************/

#include "SplayTree.h"

int main() {
    SplayTree tree;

    // Inserting elements into the tree.
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    // Print the tree in sorted order.
    std::cout << "Inorder traversal after inserts: ";
    tree.printInorder();

    // Search for an element, bringing it to the root
    tree.search(20);
    std::cout << "Inorder traversal after searching 20: ";
    tree.printInorder();

    // Delete an element.
    tree.deleteKey(10);
    std::cout << "Inorder traversal after deleting 10: ";
    tree.printInorder();

    return 0;
}
