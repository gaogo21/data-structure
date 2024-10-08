#include"priority_queue.h"

using namespace zyy;

//void test1()
//{
//	priority_queue<int> pq;
//	pq.push(4);
//	pq.push(1);
//	pq.push(5);
//	pq.push(6);
//	pq.push(2);
//
//	cout << "pq type:" << typeid(pq).name() << endl;
//	for (int i = 0; i < 5; ++i)
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//	cout << endl;
//}
//
//void test2()
//{
//	priority_queue<int, vector<int>, greater<int>> pq;
//	pq.push(4);
//	pq.push(1);
//	pq.push(5);
//	pq.push(6);
//	pq.push(2);
//
//	cout << "pq type:" << typeid(pq).name() << endl;
//	for (int i = 0; i < 5; ++i)
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//	cout << endl;
//}

void test3()
{
	std::vector<int> vec = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
	priority_queue<int> pq(vec.begin(), vec.end());
	cout << endl;
}

void test4()
{
	priority_queue<int, std::vector<int>, greater<int>> pq;
	pq.push(3);
	pq.push(1);
	pq.push(4);
	pq.push(1);
	pq.push(5);
	pq.push(9);
	pq.push(2);
	pq.push(6);
	pq.push(5);

	for (int i = 0; i < 9; ++i)
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

}
int main()
{
	test4();
	return 0;
}