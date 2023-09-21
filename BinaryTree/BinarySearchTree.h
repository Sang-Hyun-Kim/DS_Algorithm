#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

//       [ ]
//  [ ]      [ ]

struct Node
{
	Node* _parent = nullptr;
	Node* _left = nullptr;
	Node* _right = nullptr;
	int _key = {};

};



class BinarySearchTree
{
public:
	void Print() { Print(_root, 10, 0); };
	void Print(Node* node, int x, int y);

	// ���� �ް� �� ���� ��带 ���� BST�� �־���
	void	Insert(int key);
	void	Delete(int key);
	void	Delete(Node* node);
	void	Print_Inorder() { Print_Inorder(_root); }
	void	Print_Inorder(Node* node);
	void	Replace(Node* u, Node* v);
	Node*	Search(Node* node, int key);
	Node*	Search2(Node* node, int key);
	
	Node*	Min(Node* node);
	Node*	Max(Node* node);
	Node*	Next(Node* node);


private:
	Node* _root = nullptr;

};

// ������ �����ִ� ������ �߰��� ��������� ��(Rebalancing)

