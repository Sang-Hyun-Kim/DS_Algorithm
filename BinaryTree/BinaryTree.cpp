#include <iostream>

#include   "BinarySearchTree.h"
#include <thread>
using namespace std;

int main()
{
	BinarySearchTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(40);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(50);
	bst.Print();
	this_thread::sleep_for(1s);
	//bst.Print_Inorder();

	//bst.Delete(20);
	
	bst.Print();

}