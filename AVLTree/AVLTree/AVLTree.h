#pragma once
#include <iostream>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;

template <class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;


	//newһ��AVLTreeNode�ڵ��ʱ��ͻ����������캯��
	// ����������������kv
	AVLTreeNode(const pait<K, V> kv)
		:_kv(kv)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& key)
	{
		//�����Ĳ���
		//...����ƽ��
		//��������ߣ����ڵ��ƽ������-- | �������ұߣ����ڵ��ƽ������++  �����Ľڵ��Ӱ�쵽��������
	}

	bool Erase(const pair<K, V>& key)
	{

	}

private:
	Node* _root = nullptr;
};
