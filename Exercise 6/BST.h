#pragma once
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

// TreeNode class
class TreeNode
{
public:
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int value) : data(value), left(nullptr), right(nullptr) {};
};

class BST
{
public:
	// Constructors
	BST();
	~BST();
	// NOTE: copy constructor and overloaded operator not implemented

	// Mutators
	void insert(int value);
	void clear();

	// Accessors
	bool find(int value) const;
	void print() const;
	int height() const;
	bool empty() const;

private:
	TreeNode * root;

	void inOrderPrint(TreeNode* nd) const;
	void clear(TreeNode* nd);
	// Helper method for height goes here
    int numberOfNodesInLargestPath(TreeNode *root) const;
};
