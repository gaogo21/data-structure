#include "stack.h"
using namespace zyy;

void test1()
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	cout << "Õ»¶¥ÔªËØ: " << st.top() << endl;
	cout << "st.size : " << st.size() << endl;

	for (int i = 0; i < 5; ++i)
	{
		//cout << "i: " << i << " ";
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;

}

int main()
{
	test1();
	return 0;
}
