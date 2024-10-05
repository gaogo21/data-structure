#include "list.cpp"
using namespace zyy;


void test1()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.print_list();
}

void test2()
{
	list<int> lt;
	lt.push_front(1);
	lt.push_front(2);
	lt.push_front(3);
	lt.push_front(4);
	lt.push_front(5);
	lt.Insert(++lt.begin(), 10);
	lt.print_list();
}

void test3()
{
	list<int> lt;
	lt.push_front(1);
	lt.push_front(2);
	lt.push_front(3);
	lt.push_front(4);
	lt.push_front(5);
	lt.pop_back();
	lt.pop_front();
	lt.print_list();
}

void test4()
{
	list<int> lt;
	lt.push_front(1);
	lt.push_front(2);
	lt.push_front(3);
	lt.push_front(4);
	lt.push_front(5);
	lt.Erase(++lt.begin());
	lt.print_list();

	cout << lt.size() << endl;
	if (lt.Empty())
	{
		cout << "lt是空的" << endl;
	}
	else
	{
		cout << "lt不是空的" << endl;
	}
	lt.resize(10, 10);
	lt.print_list();

	cout << "lt.front(): " << lt.front() << endl;
	cout << "lt.back(): " << lt.back() << endl;
}

int main()
{
	test4();
	return 0;
}