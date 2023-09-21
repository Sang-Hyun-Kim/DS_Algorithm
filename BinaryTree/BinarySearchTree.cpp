
#include "BinarySearchTree.h"
#include <Windows.h>

// �̷� ���带 �׷��ִ� �Լ�
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	// �������̶�� �ڵ���̼� ����ü ���� ����
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
		return;
	SetCursorPosition(x, y);
	cout << node->_key;

	// Ʈ���� �׷��ֱ� ���� ������ ���
	Print(node->_left,x - ( 5 / (y + 1)), y + 1);
	Print(node->_right, x + (5 / (y + 1)), y + 1);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->_key = key;

	// BST�� ����������
	if (_root == nullptr)
	{
		// �ϳ��� �ֱ�
		_root = newNode;
		return;
	}

	// �� ���� Ž�� Ʈ���� �ƴ�
	// root���� Search ����
	Node* node = _root;
	Node* parent = nullptr; // �߰��ؾ� �ϴ� ��ġ�� parent�� ���
	
	// nullptr�� break;
	while (node)
	{
		parent = node;
		// ���� �˻����� ��庸�� ���� ��� => ��������
		// Ŭ ��� => ����������
		if (key < node->_key)
			node = node->_left;
		else
			node = node->_right;
	}

	//nullptr�� �����ؼ� ������ ���
	newNode->_parent = parent;
	
	if (key < parent->_key)
		parent->_left = newNode;
	else
		parent->_right = newNode;

}

void BinarySearchTree::Delete(int key)
{
	// ���� ��Ȳ 3����
	// 1. ������ �����͸�ã�Ҵµ� Child�� ���� ���
	//		=> �ش� ��� ������ �θ���� ���� X
	// 2. �ڽ��� �ϳ� �ִ� ���
	//		=> �ش� ��� ���� �� �ڽ� ��带 ���� �ø���
	// 3. �� ������ �ڽ��� �� �ִ� ���
	//		=> �ش� ��� ������ ���� �� �ش� ������ �������� ū ���� ã��(Next()) ���� �ø���.
	// �� �ܰ踦 Delete�� ��������� ȣ�� �� ����.

	// �ش� ������ ã��
	Node* deleteNode = Search(_root, key);

	Delete(deleteNode);



}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	// 1. ������ ����ְų� ���� �� ���� ���
	if (node->_left == nullptr)
		Replace(node, node->_right);
	// 2. �������� ����ִ� ���
	else if (node->_right == nullptr)
		Replace(node, node->_left);

	// 3.
	else // ���� �� Child �� ���� ���
	{
		// ���� ������ ã��
		Node* next = Next(node);
		node->_key = next->_key;
		Delete(next);
	}
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	// ���� Ž�� Ʈ���� 3���� ��ȸ��
	// 1. ���� ��ȸ(preorder traverse)
	// 2. ���� ��ȸ(inorder)
	// 3. ���� ��ȸ(postorder)

	// �ڽĳ�尡 ����ִٸ� Ż��
	if (node == nullptr)
		return;

	// ���� ��ȸ ���� ��� �Լ� ȣ�� 
	cout << node->_key << endl;
	Print_Inorder(node->_left);
	Print_Inorder(node->_right);



}

// u ����Ʈ���� v ����Ʈ���� ��ü
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->_parent == nullptr)
		_root = v;
	else if (u == u->_parent->_left)
		u->_parent->_left = v;
	else
		u->_parent->_right = v;

	// �ܼ��ϰ� ���� ��� u�� Nullptr�� �о������ ������ ����ϸ� �ش� �ڵ� ���� ���� ȣȯ�� ��
	if (v)
		v->_parent = u->_parent;

	delete u;

}

// ������
Node* BinarySearchTree::Search(Node* node, int key)
{
	// NullPtr�̰ų� ã�Ҵٸ� ��
	if (node == nullptr || key == node->_key)
		return node;

	if (key < node->_key)
		return Search(node->_left, key);
	else
		return Search(node->_right,key);



}

// ����
Node* BinarySearchTree::Search2(Node* node, int key)
{

	while (node && key != node->_key)
	{
		if (key < node->_key)
			node = node->_left;
		else
			node = node->_right;
	}
	return node;

}

// ���� ���� �� => ���� ���� ���� ã���� �Ǵ� �Լ�
Node* BinarySearchTree::Min(Node* node)
{
	while (node->_left)
		node = node->_left;
	return node;
}

// ���� ū �� => ���� ������ ���� ã���� �Ǵ� �Լ�
Node* BinarySearchTree::Max(Node* node)
{
	while (node->_right)
		node = node->_right;
	return node;
}

// ���� ����� key�� �������� ū key ���� ���� ���
Node* BinarySearchTree::Next(Node* node)
{
	if (node->_right)
		return Min(node->_right);
	// �̷������� ���� ������ �ڽ��� ���� �ڽ� �Ǵ� ������ �ּҰ��� ���
	// �ٸ� ����ó���� �ʿ�����

	Node* parent = node->_parent;
	// �����ʿ� �ڽ� ��尡 ������ �θ� ��� �߿��� ã�ƾ���
	// �θ� �ڽĺ��� ���� ���� ���� ����ؾ���
	
	while (parent && node == parent->_right)
	{
		node = parent;
		parent = parent->_parent;
	}
	return parent;
	// �� �θ� ��尡 �ְ� �θ��尡 ���� ��带 ������ �ڽ� ���� ������ ������
	// �θ� ���� �߿� 
	// �θ��尡 ���ų� ���� �θ� ����� ���� ����� ��� ���� ū ���� �����״� �����.

}

// BST���� �ƹ��͵� ���� ������ Nil ����� ��
// nullptr�� ǥ���ص� �ǰ� bool �����ϳ��� �Ҵ��ؼ� external �̶�� bool ������ �Ҵ��ص� ��, ������ Default Node