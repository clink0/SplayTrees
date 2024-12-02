/******************************************************
*										              *
*                CE-223 Final Project:                *
*		      Splay Tree Implementation 		      *
*													  *
*		Jett Fuller, Gavin Wakefield, Luke Bray		  *
*												      *
******************************************************/

#include "SplayTree.h"
using namespace std;

// Constructor & Destructor. 
SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() 
{
	while (root) deleteKey(root->key);
}

// Rotating a node to adjust the tree.
void SplayTree::rotate(Node* x)
{
	Node* parent = x->parent;
	Node* grandparent = parent->parent;

	if (parent->left == x) 
	{
		parent->left = x->right; 
		if (x->right) x->right->parent = parent;

		x->right = parent;
	}
	else
	{
		parent->right = x->left; 
		if (x->left) x->left->parent = parent;

		x->left = parent; 
	}

	parent->parent = x;
	x->parent = grandparent; 

	if (grandparent) 
	{
		if (grandparent->left == parent) grandparent->left = x;
		else grandparent->right = x;
	}
	else 
	{
		root = x; 
	}
}

/***********************************************************************************************
* Function for the Splay operation where node x is brought to the root.                        *
* Covers all possible splay cases:                                                             *
* Zig/Zag: Single rotation when there is no grandparent.                                       *
* Zig-Zig/Zag-Zag: Double rotation when x, its parent and grandparent form a "straight line".  *
* Zig-Zag/Zag-Zig: Double rotation when x, its parent and grandparent form a "bent line."      *
***********************************************************************************************/

void SplayTree::splay(Node* x)
{
	while (x->parent)  // Continues until x becomes the root node.
	{
		Node* parent = x->parent;
		Node* grandparent = parent->parent;

		if (!grandparent)  // Case: Zig or Zag
		{
			// Zig: x is the left child of the root.
			// Zag: x is the right child of the root.
			// Perform a single rotation to bring x to the root.
			rotate(x);
		}
		else if (grandparent->left == parent && parent->left == x)  // Case: Zig-Zig
		{
			// Zig-Zig: x is the left child of its parent, and parent is the left child of the grandparent.
			// Two right rotations are performed.
			rotate(parent); // First rotation: Bring parent above grandparent.
			rotate(x);      // Second rotation: Bring x above the parent.
		}
		else if (grandparent->right == parent && parent->right == x)  // Case: Zag-Zag
		{
			// Zag-Zag: x is the right child of its parent, and parent is the right child of the grandparent.
			// Two left rotations are performed.
			rotate(parent); // First rotation: Bring parent above grandparent.
			rotate(x);      // Second rotation: Bring x above the parent.
		}
		else if (grandparent->left == parent && parent->right == x)  // Case: Zig-Zag
		{
			// Zig-Zag: x is the right child of its parent, and parent is the left child of the grandparent.
			// A left rotation is performed followed by a right rotation.
			rotate(x);      // First rotation: Bring x above the parent
			rotate(x);      // Second rotation: Bring x above the grandparent
		}
		else if (grandparent->right == parent && parent->left == x)  // Case: Zag-Zig
		{
			// Zag-Zig: x is the left child of its parent, and parent is the right child of the grandparent.
			// A right rotation is performed followed by a left rotation.
			rotate(x);      // First rotation: Bring x above the parent
			rotate(x);      // Second rotation: Bring x above the grandparent
		}
	}
}

// Replacing a subtree rooted at u with v.

void SplayTree::replace(Node* u, Node* v)
{
	if (!u->parent)
	{
		root = v; 
	}
	else if(u == u->parent->left)
	{
		u->parent->left = v;
	}
	else 
	{
		u->parent->right = v; 
	}
	if (v) v->parent = u->parent; 
}

// Used to find the minimum node in a subtree
Node* SplayTree::subtreeMin(Node* x)
{
	while (x->left) x = x->left;
	return x;
}

// Used to insert a new key within the tree
void SplayTree::insert(int key)
{
	Node* z = root; 
	Node* p = nullptr; 

	while (z) 
	{
		p = z; 
		if (key == z->key)   // Handling for duplicate keys. 
		{
			splay(z);
			return;
		}
		else if (key < z->key)
		{
			z = z->left; 
		}
		else 
		{
			z = z->right; 
		}
	}

	Node* newNode = new Node(key); 
	newNode->parent = p; 

	if (!p) 
	{
		root = newNode; 
	}
	else if (key < p->key)
	{
		p->left = newNode;
	}
	else 
	{
		p->right = newNode; 
	}

	splay(newNode);

}

//Searching for a key and then splaying it to the root. 
Node* SplayTree::search(int key)
{
	Node* x = root;
	
	while(x)
	{
		if(key== x->key)
		{
			splay(x);
			return(x);
		}
		else if (key < x->key)
		{
			x = x->left;
		}
		else 
		{
			x = x->right; 
		}
	}
	if (!x)
	{
		cout << "Key " << key << " was not found in the tree!" << endl; 
		return nullptr; 
	}
}

// Used to delete a key from the tree. 
void SplayTree::deleteKey(int key)
{
	Node* node = search(key);

	if (!node) return;

	splay(node); 

	if (!node->left)
	{
		replace(node, node->right);
	}
	else if (!node->right)
	{
		replace(node, node->left);
	}
	else 
	{
		Node* minRight = subtreeMin(node->right);
		if (minRight->parent != node)
		{
			replace(minRight, minRight->right);
			
		}

		replace(node, minRight);
		minRight->left = node->left;
		if (node->left) node->left->parent = minRight; // Checking if node->left exists. 
	}

	delete node;
}

//Method to get the root of the tree, returning -1 if tree is empty. 
int SplayTree::getRootKey() const 
{
	return root ? root->key : -1;  
}

//For printing the tree inorder traversal (sorted order). 
void SplayTree::inorder(Node* x)
{
	if (x)
	{
		inorder(x->left);
		cout << x->key << " ";
		inorder(x->right);
	}
}

void SplayTree::printInorder()
{
	inorder(root);
	cout << endl;
}