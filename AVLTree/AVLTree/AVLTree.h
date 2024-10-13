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


	//new一个AVLTreeNode节点的时候就会调用这个构造函数
	// 如果传入参数，就是kv
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
		//搜索的插入
		//...控制平衡
		//新增在左边，父节点的平衡因子-- | 新增在右边，父节点的平衡因子++  新增的节点会影响到它的祖先
	}

	bool Erase(const pair<K, V>& key)
	{

	}

private:
	Node* _root = nullptr;
};
