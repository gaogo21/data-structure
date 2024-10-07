#pragma once
#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;

namespace zyy
{
	//建大堆
	template <class T>
	class less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	//建小堆
	template <class T>
	class greater
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};
	template <class T, class Container = std::vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		//创造一个空的priority_queue,利用缺省参数，如果不传，就是默认的less了
		priority_queue(const Compare& comFunc = Compare())
			:_comFunc(comFunc)
		{}

		//构造函数 -- 迭代器构造
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& comFunc = Compare())
		{
			//1.将数据放入堆中
			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}

			//2.建堆
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; -- i)
			{
				//传入下标， 进行向下调整  -- 向下调整是传入parent

				AdjustDown(i);
			}
		}

		void AdjustDown(int parent)
		{
			size_t child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && _con[child] < _con[child + 1])
				{
					++child;
				}

				if (_con[parent] < _con[child])
				{
					std::swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	private:
		Container _con;   //使用的vector的底层结构
		Compare _comFunc; //比较方式
	};
};