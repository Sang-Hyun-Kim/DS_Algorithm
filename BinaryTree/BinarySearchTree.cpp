
#include "BinarySearchTree.h"
#include <Windows.h>

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));

}

// �̷� ���带 �׷��ִ� �Լ�
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	// �������̶�� �ڵ���̼� ����ü ���� ����
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

BinarySearchTree::BinarySearchTree()
{
	_nil = new Node();
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
		return;
	SetCursorPosition(x, y);
	
	// ���� Ʈ���� �׷��ִ� �Լ����� ����, �� ���� �߰�
	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);


	// Ʈ���� �׷��ֱ� ���� ������ ���
	cout << node->_key;
	Print(node->_left,x - ( 5 / (y + 1)), y + 1);
	Print(node->_right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->_key = key;

	// BST�� ����������
	//if (_root == nullptr)
	//{
	//	// �ϳ��� �ֱ�
	//	_root = newNode;
	//	return;
	//}

	// �� ���� Ž�� Ʈ���� �ƴ�
	// root���� Search ����
	Node* node = _root;
	Node* parent = _nil; // �߰��ؾ� �ϴ� ��ġ�� parent�� ���
	
	// nullptr�� break;
	while (node != _nil)
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
	
	// �θ� nullptrüũ
	if (parent == _nil)
		_root = newNode;
	else if (key < parent->_key)
		parent->_left = newNode;
	else
		parent->_right = newNode;

	// Red-Black Tree�� Ư���� �����ϴ��� üũ
	newNode->_left = _nil;
	newNode->_right = _nil;
	newNode->color = Color::Red;

	// Red_Black Tree ��Ģ�� �˻�
	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
	// ��Ģ
	// 1. Parent �� Red�̰� Uncle�� Red �� ��
	// -> Parent = black, uncle = black, pp = red �� �ٲ�
	// 2. Parent �� Red�̰� Uncle�� Black �� �� (Triangle ��Ȳ)
	// -> ȸ���� ���� 3�� ���̽��� �ٲ�
	// 3. Parent �� Red�̰� Uncle�� Red �� �� (list ��Ȳ)
	// -> ���� ���� �� ȸ�� 
	// Uncle: ���� ����� �θ�� ���� �θ� ������ �θ� ���� ���� ���� �ٸ� ���

	// �θ� �����ε� �ٷ� �ڽ��� ���尡 �Ǹ� ���� �۾��� �����������
	while (node->_parent->color == Color::Red)
	{
		// �÷��� Red�� ���� ������ ����
		if (node->_parent == node->_parent->_parent->_left)
		{	// ��Ȳ
			//		[pp(B)]
			//	[p(B)]	 [u(R)]
			//		[n(R)]

			Node* uncle = node->_parent->_parent->_right;
			if (uncle->color == Color::Red)
			{	//		[pp(B)]
				//	[p(R)]	 [u(R)]
				//		[n(R)]
				// ���� ���� ���̽�
				//			=>
				//		[pp(R)]
				//	[p(B)]	 [u(B)]
				//		[n(R)]
				// �̷��� ���� ���������
				node->_parent->color = Color::Black; //p
				uncle->color = Color::Black; // u
				node->_parent->_parent->color = Color::Red; // uncle
				// �̶� ���� ����� �θ���(������ ���)�� Red��� �� �ٲپ� �����
				node = node->_parent->_parent;// �ݺ� �ȴ�!
			}
			else
			{// ��Ȳ
			//		[pp(B)]
			//	[p(R)]	 [u(B)]
			//		[n(R)]
			// �ش� ���̽��� �ΰ��� ���: Triangle�� List �� �ְ� �̸� ����ؾ� ��
			// ������ Triangle �Ʒ��� List��
			//			[pp(B)]
			//		[p(R)]	 [u(B)]
			//	[n(R)]
				if (node == node->_parent->_right) // Triangle
				{
					// �� ������ϴµ� �� �۾��� Left Rotate ��� ��
					node = node->_parent;
					LeftRotate(node);
					// �̶� ���� p��n�� �ٲ�������� �� ���
				}
				
				// List Ÿ������ ����
				//			[pp(B)]					[pp(R)]
				//		[p(R)]	 [u(B)]   =>	 [p(B)]	 [u(B)]
				//	[n(R)]					[n(R)]
				node->_parent->color = Color::Black;
				node->_parent->_parent->color = Color::Black;
				RightRotate(node->_parent->_parent);
				// ���� ȸ�� ��
				//			[p(B)]
				//		[n(R)]	 [pp(R)]
				//					[u(B)]
				// �������� B-R-B ���� + R+R �κ���
			}

		}
		else
		{
			// ��Ȳ
			//	      [pp(B)]
			//	 [u(?)]		[p(R)]	
			//					[n(R)](�¿� ���п� ���� �ڵ� �ʿ�)
			
		
			Node* uncle = node->_parent->_parent->_left;
			if (uncle->color == Color::Red) // Uncle�� Red�� ���
			{
				node->_parent->color = Color::Black; // p
				uncle->color = Color::Black; // u
				node->_parent->_parent->color = Color::Red; // pp
				node = node->_parent->_parent;
			}
			else
			{
				// ��Ȳ
				//	      [pp(B)]
				//	 [u(B)]		[p(R)]	
				//			[n(R)]
				if (node == node->_parent->_left) // Triangle Ÿ��
				{
					// ���� ������ List ���·� ��ȯ ���־�� ��
					node = node->_parent;
					RightRotate(node);
				// ��Ȳ
				//	      [pp(B)]
				//	 [u(B)]		[p(R)]	
				//					[n(R)]
				// �̶� ���� p��n�� �ٲ�������� �� ���
				}

				// List Ÿ��
				node->_parent->color = Color::Black;
				node->_parent->_parent->color = Color::Red;
				LeftRotate(node->_parent->_parent);

				//					 [p(B)]    
				//			  [pp(R)]      [n(R)]  
				//      [u(B)] 
			}
		}
	}
	_root->color = Color::Black;
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
	// nullptr ���� _nil �� ����
	if (node == _nil || key == node->_key)
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
	// �ܼ� NullCheck���� Nil���� ���� ����
	while (node->_left != _nil)
		node = node->_left;
	return node;
}

// ���� ū �� => ���� ������ ���� ã���� �Ǵ� �Լ�
Node* BinarySearchTree::Max(Node* node)
{
	// �ܼ� NullCheck���� Nil���� ���� ����
	while (node->_right != _nil)
		node = node->_right;
	return node;
}

// ���� ����� key�� �������� ū key ���� ���� ���
Node* BinarySearchTree::Next(Node* node)
{
	if (node->_right != _nil)
		return Min(node->_right);
	// �̷������� ���� ������ �ڽ��� ���� �ڽ� �Ǵ� ������ �ּҰ��� ���
	// �ٸ� ����ó���� �ʿ�����

	Node* parent = node->_parent;
	// �����ʿ� �ڽ� ��尡 ������ �θ� ��� �߿��� ã�ƾ���
	// �θ� �ڽĺ��� ���� ���� ���� ����ؾ���
	
	while (parent != _nil && node == parent->_right)
	{
		node = parent;
		parent = parent->_parent;
	}
	return parent;
	// �� �θ� ��尡 �ְ� �θ��尡 ���� ��带 ������ �ڽ� ���� ������ ������
	// �θ� ���� �߿� 
	// �θ��尡 ���ų� ���� �θ� ����� ���� ����� ��� ���� ū ���� �����״� �����.

}


void BinarySearchTree::LeftRotate(Node* x)
{
	//		[y]
	//	[x]	 [3]
	//[1][2]		
	// ��
	//			[x]
	//		[1]	  [y]
	//			[2] [3]  �� ��ȯ �ϴ� �۾�

	Node* y = x->_right;
	//2���� _nil�� ���� ����
	x->_right = y->_left; // [2]

	if (y->_left != _nil)
	{
		y->_left->_parent = x;
	}
	y->_parent = x->_parent;
	// ���� �θ���� x���� ���� �� ��������
	if (x->_parent == _nil)
	{
		_root = y;
	} 
	else if (x == x->_parent->_left)
	{
		x->_parent->_left = y;
	}
	else
		x->_parent->_right = y;

	y->_left = x;
	x->_parent = y;
}

void BinarySearchTree::RightRotate(Node* y)
{	//			[x]
	//		[1]	  [y]
	//			[2] [3]  ��
	//		[y]
	//	[x]	   [3]
	//[1][2]		�� ��ȯ

	
	Node* x = y->_left;
	//2���� _nil�� ���� ����
	y->_left = x->_right; // [2]

	if (x->_right != _nil)
		x->_right->_parent = y;

	x->_parent = y->_parent;
	// ���� �θ���� x���� ���� �� ��������
	if (y->_parent == _nil)
	{
		_root = x;
	} // 
	else if (y == y->_parent->_left)
	{
		y->_parent->_left = x;
	}
	else
		y->_parent->_right = x;

	x->_right = y;
	y->_parent = x;

}