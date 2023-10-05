
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

// 미로 보드를 그려주던 함수
void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	// 포지션이라는 코디네이션 구조체 변수 생성
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
	
	// 기존 트리를 그려주는 함수에서 변경, 색 설정 추가
	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);


	// 트리를 그려주기 위한 간단한 방법
	cout << node->_key;
	Print(node->_left,x - ( 5 / (y + 1)), y + 1);
	Print(node->_right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->_key = key;

	// BST가 비어있을경우
	//if (_root == nullptr)
	//{
	//	// 하나에 넣기
	//	_root = newNode;
	//	return;
	//}

	// 빈 이진 탐색 트리가 아님
	// root부터 Search 시작
	Node* node = _root;
	Node* parent = _nil; // 추가해야 하는 위치를 parent로 기억
	
	// nullptr시 break;
	while (node != _nil)
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
	
	// 부모 nullptr체크
	if (parent == _nil)
		_root = newNode;
	else if (key < parent->_key)
		parent->_left = newNode;
	else
		parent->_right = newNode;

	// Red-Black Tree의 특성을 만족하는지 체크
	newNode->_left = _nil;
	newNode->_right = _nil;
	newNode->color = Color::Red;

	// Red_Black Tree 규칙성 검사
	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
	// 규칙
	// 1. Parent 가 Red이고 Uncle이 Red 일 때
	// -> Parent = black, uncle = black, pp = red 로 바꿈
	// 2. Parent 가 Red이고 Uncle이 Black 일 때 (Triangle 상황)
	// -> 회전을 통해 3번 케이스로 바꿈
	// 3. Parent 가 Red이고 Uncle이 Red 일 때 (list 상황)
	// -> 색상 변경 및 회전 
	// Uncle: 현재 노드의 부모와 같은 부모를 가지며 부모 노드와 같은 층인 다른 노드

	// 부모가 레드인데 바로 자식이 레드가 되면 수정 작업을 진행해줘야함
	while (node->_parent->color == Color::Red)
	{
		// 컬러가 Red가 나올 때까지 실행
		if (node->_parent == node->_parent->_parent->_left)
		{	// 상황
			//		[pp(B)]
			//	[p(B)]	 [u(R)]
			//		[n(R)]

			Node* uncle = node->_parent->_parent->_right;
			if (uncle->color == Color::Red)
			{	//		[pp(B)]
				//	[p(R)]	 [u(R)]
				//		[n(R)]
				// 제일 쉬운 케이스
				//			=>
				//		[pp(R)]
				//	[p(B)]	 [u(B)]
				//		[n(R)]
				// 이렇게 변경 시켜줘야함
				node->_parent->color = Color::Black; //p
				uncle->color = Color::Black; // u
				node->_parent->_parent->color = Color::Red; // uncle
				// 이때 조부 노드의 부모노드(증조부 노드)가 Red라면 또 바꾸어 줘야함
				node = node->_parent->_parent;// 반복 된다!
			}
			else
			{// 상황
			//		[pp(B)]
			//	[p(R)]	 [u(B)]
			//		[n(R)]
			// 해당 케이스는 두가지 모습: Triangle과 List 가 있고 이를 대비해야 함
			// 위에는 Triangle 아래는 List임
			//			[pp(B)]
			//		[p(R)]	 [u(B)]
			//	[n(R)]
				if (node == node->_parent->_right) // Triangle
				{
					// 쭉 펴줘야하는데 이 작업을 Left Rotate 라고 함
					node = node->_parent;
					LeftRotate(node);
					// 이때 기존 p와n이 바뀌어있음을 꼭 기억
				}
				
				// List 타입으로 변경
				//			[pp(B)]					[pp(R)]
				//		[p(R)]	 [u(B)]   =>	 [p(B)]	 [u(B)]
				//	[n(R)]					[n(R)]
				node->_parent->color = Color::Black;
				node->_parent->_parent->color = Color::Black;
				RightRotate(node->_parent->_parent);
				// 오른 회전 후
				//			[p(B)]
				//		[n(R)]	 [pp(R)]
				//					[u(B)]
				// 안정적인 B-R-B 구조 + R+R 로변경
			}

		}
		else
		{
			// 상황
			//	      [pp(B)]
			//	 [u(?)]		[p(R)]	
			//					[n(R)](좌우 구분에 따른 코드 필요)
			
		
			Node* uncle = node->_parent->_parent->_left;
			if (uncle->color == Color::Red) // Uncle이 Red일 경우
			{
				node->_parent->color = Color::Black; // p
				uncle->color = Color::Black; // u
				node->_parent->_parent->color = Color::Red; // pp
				node = node->_parent->_parent;
			}
			else
			{
				// 상황
				//	      [pp(B)]
				//	 [u(B)]		[p(R)]	
				//			[n(R)]
				if (node == node->_parent->_left) // Triangle 타입
				{
					// 꺽여 있으니 List 형태로 변환 해주어야 함
					node = node->_parent;
					RightRotate(node);
				// 상황
				//	      [pp(B)]
				//	 [u(B)]		[p(R)]	
				//					[n(R)]
				// 이때 기존 p와n이 바뀌어있음을 꼭 기억
				}

				// List 타입
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
	// nullptr 에서 _nil 로 변경
	if (node == _nil || key == node->_key)
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
	// 단순 NullCheck에서 Nil과의 차이 구분
	while (node->_left != _nil)
		node = node->_left;
	return node;
}

// 가장 큰 값 => 가장 오른쪽 값을 찾으면 되는 함수
Node* BinarySearchTree::Max(Node* node)
{
	// 단순 NullCheck에서 Nil과의 차이 구분
	while (node->_right != _nil)
		node = node->_right;
	return node;
}

// 넣은 노드의 key값 다음으로 큰 key 값을 가진 노드
Node* BinarySearchTree::Next(Node* node)
{
	if (node->_right != _nil)
		return Min(node->_right);
	// 이론적으론 나의 오른쪽 자식의 왼쪽 자식 또는 그쪽의 최소값이 대상
	// 다만 예외처리가 필요해짐

	Node* parent = node->_parent;
	// 오른쪽에 자식 노드가 없으면 부모 노드 중에서 찾아야함
	// 부모가 자식보다 작은 값을 때를 고려해야함
	
	while (parent != _nil && node == parent->_right)
	{
		node = parent;
		parent = parent->_parent;
	}
	return parent;
	// 즉 부모 노드가 있고 부모노드가 현재 노드를 오른쪽 자식 노드로 가지고 있을때
	// 부모 노드들 중에 
	// 부모노드가 없거나 내가 부모 노드의 왼쪽 노드일 경우 다음 큰 값이 없을테니 벗어난다.

}


void BinarySearchTree::LeftRotate(Node* x)
{
	//		[y]
	//	[x]	 [3]
	//[1][2]		
	// 를
	//			[x]
	//		[1]	  [y]
	//			[2] [3]  로 변환 하는 작업

	Node* y = x->_right;
	//2번이 _nil일 수도 있음
	x->_right = y->_left; // [2]

	if (y->_left != _nil)
	{
		y->_left->_parent = x;
	}
	y->_parent = x->_parent;
	// 기존 부모노드와 x와의 관계 를 따져야함
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
	//			[2] [3]  를
	//		[y]
	//	[x]	   [3]
	//[1][2]		로 변환

	
	Node* x = y->_left;
	//2번이 _nil일 수도 있음
	y->_left = x->_right; // [2]

	if (x->_right != _nil)
		x->_right->_parent = y;

	x->_parent = y->_parent;
	// 기존 부모노드와 x와의 관계 를 따져야함
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