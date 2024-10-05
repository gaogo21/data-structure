#include "list.h"
//template<class T>
//zyy::list<T>::list()
//{
//	_head = new Node;
//	_head->_prev = _head; //指向自己
//	_head->_next = _head; //指向自己
//}

template <class T>
void zyy::list<T>::empty_init()
{
	_head = new Node;
	_head->_prev = _head; //指向自己
	_head->_next = _head; //指向自己
}

template <class T>
zyy::list<T>::list(list<T>& lt)
{
	//1.构造一个头结点
	empty_init();
	//2.迭代器构造一个tmp，内容和lt相同
	list<T> tmp(lt.begin(), lt.end());
	//3.交换tmp的头结点和头结点
	std::swap(tmp._head, _head);
}

template<class T>
zyy::list<T>::list(size_t n, const T& x)
{
	//1.创造一个头结点
	empty_init();
	//2.将n个x尾插进来
	for (int i = 0; i < n; ++i)
	{
		push_back(x);
	}
}

//template<class T>
//zyy::list<T>& zyy::list<T>::operator=(list<T>& lt)
//{
//	//将原来的内容清空
//	clear();
//	if (this != &lt) //避免自己复制自己
//	{
//		for (auto e : lt)
//		{
//			push_back(e);
//		}
//	}
//
//	return *this;
//}

template<class T>
void  zyy::list<T>::swap(list<T>& tmp)
{
	std::swap(_head, tmp._head);
}

template<class T>
zyy::list<T>& zyy::list<T>::operator=(list<T> lt)
{
	swap(lt);

	return *this;
}

//template<class T>
//void zyy::list<T>::clear()
//{
//	auto it = begin();
//	while (it != end())
//	{
//		it = Erase(it);
//	}
//}

//template<class T>
//zyy::list<T>::~list()
//{
//	//1.清空
//	clear();
//	//2.delete掉头结点
//	delete _head;
//	//3.置空
//	_head = nullptr;
//}

template<class T>
typename zyy::list<T>::iterator zyy::list<T>::begin()
{
	return iterator(_head->_next);
}

template<class T>
typename zyy::list<T>::iterator zyy::list<T>::end()
{
	return iterator(_head);
}

template<class T>
typename zyy::list<T>::const_iterator zyy::list<T>::begin() const
{
	return const_iterator(_head->_next);
}

template<class T>
typename zyy::list<T>::const_iterator zyy::list<T>::end() const
{
	return const_iterator(_head);
}

template<class T>
T& zyy::list<T>::front()
{
	return *begin();
}

template<class T>
T& zyy::list<T>::back()
{
	return *(--end());
}

template<class T>
const T& zyy::list<T>::front()	const
{
	return *begin();
}

template<class T>
const T& zyy::list<T>::back()	const
{
	return *(--end());
}

template<class T>
typename zyy::list<T>::iterator zyy::list<T>::Insert(iterator pos, const T& x)
{
	assert(pos._node);

	//1.找到cur和prev
	Node* cur = pos._node;
	Node* prev = cur->_prev;
	//2.创建一个新的结点newnode
	Node* newnode = new Node(x);

	//3.建立newnode和prev的双向关系
	prev->_next = newnode;
	newnode->_prev = prev;

	//4.建立newnode和cur的双向关系
	cur->_prev = newnode;
	newnode->_next = cur;

	return iterator(newnode);
}

template<class T>
typename zyy::list<T>::iterator zyy::list<T>::Erase(iterator pos)
{
	assert(pos._node); //检测pos的合法性
	assert(pos != end()); //删除的结点不能是头结点

	Node* cur = pos._node; //迭代器pos处的结点指针
	Node* prev = cur->_prev; //迭代器pos前一个位置的结点指针
	Node* next = cur->_next; //迭代器pos后一个位置的结点指针

	delete cur; //释放cur结点

	//建立prev与next之间的双向关系
	prev->_next = next;
	next->_prev = prev;

	return iterator(next); //返回所给迭代器pos的下一个迭代器
}