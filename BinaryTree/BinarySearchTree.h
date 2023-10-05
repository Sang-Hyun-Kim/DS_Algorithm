#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

//       [ ]
//  [ ]      [ ]

// Red-Black 트리를 위한 수정
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
// 1. 모든 노드는 Red 또는 Black의 색 속성을 가진다.
// 2. Root 노드는 Black 이다.
// 3. Leaf(NIL)는 Black 이다.
// 4. Red 노드의 자식노드는 Black이다. 즉 연속된 Red 노드의 반복이 생성 X
// 5.각 노드로 부터 - 리프로 가는 경로들은 모두 같은 수의 Black 노드를 가진다.
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	void Print() { Print(_root, 10, 0); };
	void Print(Node* node, int x, int y);

	// 값을 받고 그 값의 노드를 만들어서 BST에 넣어줌
	void	Insert(int key);
	// Red_Black_Tree 규칙을 검사하는 함수
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
	// 기존 없을 때마다 nullcheck 할때 사용되며 색의 속성(Black)도 가지고 있는
	// 자식노드 공간이 비어있는 것을 표현할 때 사용된다.
	Node* _nil = nullptr;

};

// 균형을 맞춰주는 구조를 추가로 제작해줘야 함(Rebalancing)


// BST에서 아무것도 없는 공간을 Nil 노드라고 함
// nullptr로 표현해도 되고 bool 변수하나를 할당해서 external 이라는 bool 값으로 할당해도 됨, 일종의 Default Node