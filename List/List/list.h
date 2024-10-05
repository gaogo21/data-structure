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

		//构造函数
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
		//前置++   --> 返回++之后的内容
		self& operator++()
		{
			_node = _node->_next;
			return *this;   //this表示self*类型，所以要对this解引用
		}

		//后置++  --> 返回++之前的内容
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
		//迭代器
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//构造函数
		list()
		{
			_head = new Node;
			_head->_prev = _head; //指向自己
			_head->_next = _head; //指向自己
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
			//1.清空
			clear();
			//2.delete掉头结点
			delete _head;
			//3.置空
			_head = nullptr;
		}
		//拷贝构造
		list(list<T>& lt);
		
		//初始化一个循环链表
		void empty_init();

		//list<T>& operator=(list<T>& lt);
		//赋值构造   -- 传递值，而不是引用
		list<T>& operator=(list<T> lt);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//容量相关的函数
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
			iterator i = begin(); //获取第一个有效数据的迭代器
			size_t len = 0; //记录当前所遍历的数据个数
			while (len < n && i != end())
			{
				len++;
				i++;
			}
			if (len == n) //说明容器当中的有效数据个数大于或是等于n
			{
				while (i != end()) //只保留前n个有效数据
				{
					i = Erase(i); //每次删除后接收下一个数据的迭代器
				}
			}
			else //说明容器当中的有效数据个数小于n
			{
				while (len < n) //尾插数据为val的结点，直到容器当中的有效数据个数为n
				{
					push_back(val);
					len++;
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//访问容器相关的函数
		T& front();
		T& back();
		const T& front()	const;
		const T& back()	const;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//修改相关的函数
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