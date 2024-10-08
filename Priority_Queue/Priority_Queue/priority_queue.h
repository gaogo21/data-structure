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
	public:
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	//��С��
	template <class T>
	class greater
	{
	public:
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

			//�ҵ����Һ����д����һ��
			while (child < _con.size())
			{
				//if (child + 1 < _con.size() && _con[child] < _con[child + 1])
				if (child + 1 < _con.size() && _comFunc(_con[child], _con[child + 1]))
				{
					++child;
				}

				//if (_con[parent] < _con[child])
				if (_comFunc(_con[parent], _con[child]))
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

		//�������child,һ���ǲ���������ϵ���
		void AdjustUp(int child)
		{
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				//�Ѵ�����ϵ�
				//if (_con[parent] < _con[child])
				if (_comFunc(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					//child���ϵ�
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			//1.��x���뵽ĩβ
			_con.push_back(x);

			//2.���ϵ��� -- ���һ��Ԫ��
			AdjustUp(_con.size() - 1);
		}

		void pop()
		{
			if (empty())
				return;
			//1.���Ѷ�Ԫ�غͶѵ�Ԫ�ؽ���
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

		T& top()
		{
			return _con[0];
		}
	private:
		Container _con;   //ʹ�õ�vector�ĵײ�ṹ
		Compare _comFunc; //�ȽϷ�ʽ
	};
};