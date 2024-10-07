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
	//�����
	template <class T>
	class less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	//��С��
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
		//����һ���յ�priority_queue,����ȱʡ�������������������Ĭ�ϵ�less��
		priority_queue(const Compare& comFunc = Compare())
			:_comFunc(comFunc)
		{}

		//���캯�� -- ����������
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& comFunc = Compare())
		{
			//1.�����ݷ������
			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}

			//2.����
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; -- i)
			{
				//�����±꣬ �������µ���  -- ���µ����Ǵ���parent

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
		Container _con;   //ʹ�õ�vector�ĵײ�ṹ
		Compare _comFunc; //�ȽϷ�ʽ
	};
};