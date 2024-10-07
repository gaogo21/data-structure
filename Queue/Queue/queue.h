#pragma once
#include <iostream>
#include <deque>

using std::endl;
using std::cout;
using std::istream;
using std::ostream;

namespace zyy
{
	//queue -> 先进先出
	template <class T, class Container = std::deque<T>>
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}

		size_t size() const
		{
			return _con.size();
		}

		T& top()
		{
			return _con.front();
		}

		const T& top() const
		{
			return _con.front();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
};
