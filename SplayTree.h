/******************************************************
*										              *
*                CE-223 Final Project:                *
*		      Splay Tree Implementation 		      *
*													  *
*		Jett Fuller, Gavin Wakefield, Luke Bray		  *
*												      *
******************************************************/

#pragma once
#include <iostream>

struct Node 
{
	int key; 
	Node* left; 
	Node* right; 
	Node* parent; 

	Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}

};

class SplayTree
{
private:

	Node* root;

	void rotate(Node* x);
	void splay(Node* x);
	void replace(Node* u, Node* v);
	Node* subtreeMin(Node* x);
	void inorder(Node* x);

public:

	SplayTree();
	~SplayTree();

	void insert(int key);
	Node* search(int key);
	void deleteKey(int key);
	void printInorder();
	int getRootKey() const; 
};
