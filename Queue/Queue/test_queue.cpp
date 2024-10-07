#include "queue.h"

using namespace zyy;

void test1()
{
	queue<int> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);

	cout << "q1.top(): " << q1.top() << endl;
	cout << "before size: " << q1.size() << endl;
	cout << "before empty: " << q1.empty() << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << q1.top() << " ";
		q1.pop();
	}
	cout << endl;
	cout << "after size: " << q1.size() << endl;
	cout << "after empty: " << q1.empty() << endl;
}

int main()
{
	test1();
	return 0;
}