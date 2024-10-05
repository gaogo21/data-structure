#pragma once

#include<iostream>
#include<assert.h>
#include<string>

using std::istream;
using std::ostream;
using std::endl;
using std::cout;

namespace zyy
{
	template <class T>
	struct ListNode
	{
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _data;

		//���캯��
		ListNode(const T& x = T())
			:_prev(nullptr)
			,_next(nullptr)
			,_data(x)
		{}
	};

	template <class T, class Ref, class Ptr>
	class __list_iterator
	{
	public:
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;

		__list_iterator(Node* node = nullptr)
			:_node(node)
		{}
	public:
		//ǰ��++   --> ����++֮�������
		self& operator++()
		{
			_node = _node->_next;
			return *this;   //this��ʾself*���ͣ�����Ҫ��this������
		}

		//����++  --> ����++֮ǰ������
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const self& s)	const
		{
			return _node != s._node;
		}

		bool operator==(const self& s)	const
		{
			return _node == s._node;
		}

		Node* _node;
	};
	

	template <class T>
	class list
	{
	public:
		typedef ListNode<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<const T, const T&, const T*> const_iterator;

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//������
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���캯��
		list()
		{
			_head = new Node;
			_head->_prev = _head; //ָ���Լ�
			_head->_next = _head; //ָ���Լ�
		}
		list(size_t n, const T& x = T());
		list(iterator first, iterator last)
		{
			empty_init();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		~list()
		{
			//1.���
			clear();
			//2.delete��ͷ���
			delete _head;
			//3.�ÿ�
			_head = nullptr;
		}
		//��������
		list(list<T>& lt);
		
		//��ʼ��һ��ѭ������
		void empty_init();

		//list<T>& operator=(list<T>& lt);
		//��ֵ����   -- ����ֵ������������
		list<T>& operator=(list<T> lt);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//������صĺ���
		size_t size()
		{
			int n = 0;
			auto it = begin();
			while (it != end())
			{
				++it;
				++n;
			}

			return n;
		}

		bool Empty()
		{
			return begin() == end();
		}
		void clear()
		{
			auto it = begin();
			while (it != end())
			{
				it = Erase(it);
			}
		}
		void resize(size_t n, const T& val = T())
		{
			iterator i = begin(); //��ȡ��һ����Ч���ݵĵ�����
			size_t len = 0; //��¼��ǰ�����������ݸ���
			while (len < n && i != end())
			{
				len++;
				i++;
			}
			if (len == n) //˵���������е���Ч���ݸ������ڻ��ǵ���n
			{
				while (i != end()) //ֻ����ǰn����Ч����
				{
					i = Erase(i); //ÿ��ɾ���������һ�����ݵĵ�����
				}
			}
			else //˵���������е���Ч���ݸ���С��n
			{
				while (len < n) //β������Ϊval�Ľ�㣬ֱ���������е���Ч���ݸ���Ϊn
				{
					push_back(val);
					len++;
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//����������صĺ���
		T& front();
		T& back();
		const T& front()	const;
		const T& back()	const;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//�޸���صĺ���
		void push_back(const T& x)
		{
			Insert(end(), x);
		}
		void pop_back()
		{
			Erase(--end());
		}
		void push_front(const T& x)
		{
			Insert(begin(), x);
		}
		void pop_front()
		{
			Erase(begin());
		}
		iterator Insert(iterator pos, const T& x);
		iterator Erase(iterator pos);
		void swap(list<T>& tmp);
		void print_list()
		{
			auto it = begin();
			while (it != end())
			{
				cout << *it << " ";
				++it;
			}
			cout << endl;
		}
	private:
		Node* _head;
	};
};