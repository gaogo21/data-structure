#include "BinarySearchTree.h"

using namespace zyy;

void test1()
{
	BSTree<int> bst;
	bst.Insert(1);
	bst.Insert(3);
	bst.Insert(4);
	bst.Insert(6);
	bst.Insert(0);
	bst.Insert(2);

	if (bst.Find(3))
	{
		cout << "找到了" << endl;
	}
	else
	{
		cout << "没找到" << endl;
	}

	bst.Inorder();
}

void test2()
{
	BSTree<int> bst;
	bst.Insert(8);
	bst.Insert(1);
	bst.Insert(3);
	bst.Insert(6);
	bst.Insert(4);
	bst.Insert(7);
	bst.Insert(10);
	bst.Insert(14);
	bst.Insert(13);

	cout << "before: ";
	bst.Inorder();


	//1.测试没有孩子
	//bst.Erase(7);

	//2.测试有一个孩子 -> 有右孩子
	//bst.Erase(10);

	//3.测试有一个孩子 -> 有左孩子
	bst.Erase(14);
	
	//4.测试有两个孩子
	//bst.Erase(6);

	cout << "after: ";
	bst.Inorder();
}
int main()
{
	test2();
	return 0;
}