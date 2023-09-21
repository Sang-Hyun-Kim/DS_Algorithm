
#include "BinarySearchTree.h"
#include <Windows.h>

// 미로 보드를 그려주던 함수
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	// 포지션이라는 코디네이션 구조체 변수 생성
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nullptr)
		return;
	SetCursorPosition(x, y);
	cout << node->_key;

	// 트리를 그려주기 위한 간단한 방법
	Print(node->_left,x - ( 5 / (y + 1)), y + 1);
	Print(node->_right, x + (5 / (y + 1)), y + 1);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->_key = key;

	// BST가 비어있을경우
	if (_root == nullptr)
	{
		// 하나에 넣기
		_root = newNode;
		return;
	}

	// 빈 이진 탐색 트리가 아님
	// root부터 Search 시작
	Node* node = _root;
	Node* parent = nullptr; // 추가해야 하는 위치를 parent로 기억
	
	// nullptr시 break;
	while (node)
	{
		parent = node;
		// 현재 검색중인 노드보다 작을 경우 => 왼쪽으로
		// 클 경우 => 오른쪽으로
		if (key < node->_key)
			node = node->_left;
		else
			node = node->_right;
	}

	//nullptr에 도착해서 끝났을 경우
	newNode->_parent = parent;
	
	if (key < parent->_key)
		parent->_left = newNode;
	else
		parent->_right = newNode;

}

void BinarySearchTree::Delete(int key)
{
	// 삭제 상황 3가지
	// 1. 삭제할 데이터를찾았는데 Child가 없을 경우
	//		=> 해당 노드 삭제후 부모노드와 연결 X
	// 2. 자식이 하나 있는 경우
	//		=> 해당 노드 삭제 후 자식 노드를 위로 올리기
	// 3. 양 옆으로 자식이 다 있는 경우
	//		=> 해당 노드 데이터 삭제 및 해당 데이터 다음으로 큰 수를 찾아(Next()) 위로 올린다.
	// 각 단계를 Delete가 재귀적으로 호출 될 것임.

	// 해당 데이터 찾기
	Node* deleteNode = Search(_root, key);

	Delete(deleteNode);



}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	// 1. 왼쪽이 비어있거나 양쪽 다 없는 경우
	if (node->_left == nullptr)
		Replace(node, node->_right);
	// 2. 오른쪽이 비어있는 경우
	else if (node->_right == nullptr)
		Replace(node, node->_left);

	// 3.
	else // 양쪽 다 Child 가 있을 경우
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		node->_key = next->_key;
		Delete(next);
	}
}

void BinarySearchTree::Print_Inorder(Node* node)
{
	// 이진 탐색 트리의 3가지 순회법
	// 1. 전위 순회(preorder traverse)
	// 2. 중위 순회(inorder)
	// 3. 후위 순회(postorder)

	// 자식노드가 비어있다면 탈출
	if (node == nullptr)
		return;

	// 중위 순회 기준 재귀 함수 호출 
	cout << node->_key << endl;
	Print_Inorder(node->_left);
	Print_Inorder(node->_right);



}

// u 서브트리를 v 서브트리로 교체
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->_parent == nullptr)
		_root = v;
	else if (u == u->_parent->_left)
		u->_parent->_left = v;
	else
		u->_parent->_right = v;

	// 단순하게 기존 노드 u를 Nullptr로 밀어버리고 싶을때 사용하면 해당 코드 제외 전부 호환이 됨
	if (v)
		v->_parent = u->_parent;

	delete u;

}

// 직관성
Node* BinarySearchTree::Search(Node* node, int key)
{
	// NullPtr이거나 찾았다면 끝
	if (node == nullptr || key == node->_key)
		return node;

	if (key < node->_key)
		return Search(node->_left, key);
	else
		return Search(node->_right,key);



}

// 성능
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

// 가장 작은 값 => 가장 왼쪽 값을 찾으면 되는 함수
Node* BinarySearchTree::Min(Node* node)
{
	while (node->_left)
		node = node->_left;
	return node;
}

// 가장 큰 값 => 가장 오른쪽 값을 찾으면 되는 함수
Node* BinarySearchTree::Max(Node* node)
{
	while (node->_right)
		node = node->_right;
	return node;
}

// 넣은 노드의 key값 다음으로 큰 key 값을 가진 노드
Node* BinarySearchTree::Next(Node* node)
{
	if (node->_right)
		return Min(node->_right);
	// 이론적으론 나의 오른쪽 자식의 왼쪽 자식 또는 그쪽의 최소값이 대상
	// 다만 예외처리가 필요해짐

	Node* parent = node->_parent;
	// 오른쪽에 자식 노드가 없으면 부모 노드 중에서 찾아야함
	// 부모가 자식보다 작은 값을 때를 고려해야함
	
	while (parent && node == parent->_right)
	{
		node = parent;
		parent = parent->_parent;
	}
	return parent;
	// 즉 부모 노드가 있고 부모노드가 현재 노드를 오른쪽 자식 노드로 가지고 있을때
	// 부모 노드들 중에 
	// 부모노드가 없거나 내가 부모 노드의 왼쪽 노드일 경우 다음 큰 값이 없을테니 벗어난다.

}

// BST에서 아무것도 없는 공간을 Nil 노드라고 함
// nullptr로 표현해도 되고 bool 변수하나를 할당해서 external 이라는 bool 값으로 할당해도 됨, 일종의 Default Node