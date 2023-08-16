#pragma once
#include <iostream>
#include <list>

template<class T>
class Node // 하나의 데이터 단위
{

public:
	Node() : _prev(nullptr), _next(nullptr), _data(T())
	{

	}
	Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
	{

	}


public:
	Node* _prev;
	Node* _next;
	T _data;

};
// 포인터 주소를 통해 앞뒤로 이동


// iterator 구현
template<class T>
class Iterator
{
public:
	Iterator() : _node(nullptr)
	{

	}
	Iterator(Node<T>* node) : _node(node)
	{

	}
	~Iterator() {}

	// ++it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}
	//--it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	//*it
	T& operator*()
	{
		return _node->_data;
	}

	bool operator==(const Iterator& other)
	{
		return _node == other._node;
	}

	bool operator!=(const Iterator& other)
	{
		return _node != other._node;
	}

public:
	Node<T>* _node;
};



template<class T>
class List
{
public:

	List() :_size(0)
	{
		// 초기화시 더미 노드 지정
		_head = new Node<T>();
		_tail = new Node<T>();
		_head->_next = _tail;
		_tail->_prev = _head;
	}

	~List()
	{
		while (_size > 0)
		{
			pop_back();
		}
		delete _head;
		delete _tail;
	}

public:

	void push_back(const T& value)
	{
		AddNode(_tail, value);
	}

	void pop_back()
	{
		RemoveNode(_tail->_prev);
	}

private:
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		Node<T>* newNode = new Node<T>(value);	
		Node<T>* prevNode = before->_prev;

		prevNode->_next = newNode;
		newNode->_prev = prevNode;

		newNode->_next = before;
		before->_prev = newNode;

		_size++;

		return newNode;
	}

	Node<T>* RemoveNode(Node<T>* node)
	{
		Node<T>* prevNode = node->_prev;
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;
		_size--;

		return nextNode;
	}

	int size() {return _size;}


public:
	using iterator = Iterator<T>;
	iterator begin() { return iterator(_head->_next); }
	iterator end() { return iterator(_tail); }

	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}

private:
	Node<T>* _head;
	Node<T>* _tail;

	int _size;

};


// list는 vector랑 다르게 전방삽입이 가능
// vector는 push_front를 할 경우 연속된 데이터가 전부 옮겨져야하는 불상사가 생김
// list는 노드 하나 만들고 연결만하면된다.
// list는 []연산자를 사용할 수 없다. 즉 임의 접근이 불가능하다
// vector의 장점인 연속된 데이터의 모임이 아니기 때문이다.
 
// 더 나아가면 트리, 그래프로 만들 수 있다.
// list의 중간 삽입 삭제가 빠르다는 것은
// 어쩌피 위치를 모르면 위치 탐색(N)을 소모해야하는 것은 같지만
// iterator를 통해 주소값을 저장해 놓을 경우 바로 접근이 가능하기때문에
// 빠르다는 것을 꼭 알아라..
// 즉 삽입,삭제를 할 곳을 알고 있어야 "조건부"적으로 빠르다 라는 것을
// 숙지해라