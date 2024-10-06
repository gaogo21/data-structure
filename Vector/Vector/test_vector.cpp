#include "vector.h"

using namespace zyy;

void test1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);

	v1.pop_back();

	v1.insert(v1.begin(), 10);
	auto it = v1.end();
	--it;
	v1.erase(it);


	//将容量扩大到n
	cout << "before capacity: " << v1.capacity() << endl;
	cout << "before size：" << v1.size() << endl;
	v1.reserve(10);
	cout << "after size：" << v1.size() << endl;
	cout << "after capacity: " << v1.capacity() << endl;
	v1.print();
}
int main()
{
	test1();
}