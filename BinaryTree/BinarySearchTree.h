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
	//RED-BLACK
	Node* _nil = nullptr;

};

// 균형을 맞춰주는 구조를 추가로 제작해줘야 함(Rebalancing)

