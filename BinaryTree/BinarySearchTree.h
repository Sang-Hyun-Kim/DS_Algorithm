#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

//       [ ]
//  [ ]      [ ]

// Red-Black Ʈ���� ���� ����
enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node* _parent = nullptr;
	Node* _left = nullptr;
	Node* _right = nullptr;
	int _key = {};
	Color color = Color::Black;
};

// RedBlack Tree
// 1. ��� ���� Red �Ǵ� Black�� �� �Ӽ��� ������.
// 2. Root ���� Black �̴�.
// 3. Leaf(NIL)�� Black �̴�.
// 4. Red ����� �ڽĳ��� Black�̴�. �� ���ӵ� Red ����� �ݺ��� ���� X
// 5.�� ���� ���� - ������ ���� ��ε��� ��� ���� ���� Black ��带 ������.
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	void Print() { Print(_root, 10, 0); };
	void Print(Node* node, int x, int y);

	// ���� �ް� �� ���� ��带 ���� BST�� �־���
	void	Insert(int key);
	// Red_Black_Tree ��Ģ�� �˻��ϴ� �Լ�
	void	InsertFixup(Node* node);
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

	// Red_Black_Tree
	void LeftRotate(Node* x);
	void RightRotate(Node* y);


private:
	Node* _root = nullptr; 
	//RED-BLACK
	// ���� ���� ������ nullcheck �Ҷ� ���Ǹ� ���� �Ӽ�(Black)�� ������ �ִ�
	// �ڽĳ�� ������ ����ִ� ���� ǥ���� �� ���ȴ�.
	Node* _nil = nullptr;

};

// ������ �����ִ� ������ �߰��� ��������� ��(Rebalancing)


// BST���� �ƹ��͵� ���� ������ Nil ����� ��
// nullptr�� ǥ���ص� �ǰ� bool �����ϳ��� �Ҵ��ؼ� external �̶�� bool ������ �Ҵ��ص� ��, ������ Default Node