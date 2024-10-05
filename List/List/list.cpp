#include "list.h"
//template<class T>
//zyy::list<T>::list()
//{
//	_head = new Node;
//	_head->_prev = _head; //ָ���Լ�
//	_head->_next = _head; //ָ���Լ�
//}

template <class T>
void zyy::list<T>::empty_init()
{
	_head = new Node;
	_head->_prev = _head; //ָ���Լ�
	_head->_next = _head; //ָ���Լ�
}

template <class T>
zyy::list<T>::list(list<T>& lt)
{
	//1.����һ��ͷ���
	empty_init();
	//2.����������һ��tmp�����ݺ�lt��ͬ
	list<T> tmp(lt.begin(), lt.end());
	//3.����tmp��ͷ����ͷ���
	std::swap(tmp._head, _head);
}

template<class T>
zyy::list<T>::list(size_t n, const T& x)
{
	//1.����һ��ͷ���
	empty_init();
	//2.��n��xβ�����
	for (int i = 0; i < n; ++i)
	{
		push_back(x);
	}
}

//template<class T>
//zyy::list<T>& zyy::list<T>::operator=(list<T>& lt)
//{
//	//��ԭ�����������
//	clear();
//	if (this != &lt) //�����Լ������Լ�
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
//	//1.���
//	clear();
//	//2.delete��ͷ���
//	delete _head;
//	//3.�ÿ�
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

	//1.�ҵ�cur��prev
	Node* cur = pos._node;
	Node* prev = cur->_prev;
	//2.����һ���µĽ��newnode
	Node* newnode = new Node(x);

	//3.����newnode��prev��˫���ϵ
	prev->_next = newnode;
	newnode->_prev = prev;

	//4.����newnode��cur��˫���ϵ
	cur->_prev = newnode;
	newnode->_next = cur;

	return iterator(newnode);
}

template<class T>
typename zyy::list<T>::iterator zyy::list<T>::Erase(iterator pos)
{
	assert(pos._node); //���pos�ĺϷ���
	assert(pos != end()); //ɾ���Ľ�㲻����ͷ���

	Node* cur = pos._node; //������pos���Ľ��ָ��
	Node* prev = cur->_prev; //������posǰһ��λ�õĽ��ָ��
	Node* next = cur->_next; //������pos��һ��λ�õĽ��ָ��

	delete cur; //�ͷ�cur���

	//����prev��next֮���˫���ϵ
	prev->_next = next;
	next->_prev = prev;

	return iterator(next); //��������������pos����һ��������
}