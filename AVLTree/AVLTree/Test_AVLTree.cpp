#include "AVLTree.h"


void testAVL1()
{
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.IsBalance();
	t.Inorder();
}

int main()
{
	testAVL1();
	return 0;
}