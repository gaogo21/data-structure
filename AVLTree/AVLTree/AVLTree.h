#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

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
	AVLTreeNode(const pair<K, V>& kv)
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
	bool Insert(const pair<K, V>& kv)
	{
		//搜索的插入
		//...控制平衡
		//新增在左边，父节点的平衡因子-- | 新增在右边，父节点的平衡因子++  新增的节点会影响到它的祖先
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				assert("插入相同的节点");
			}
		}

		//走到这里，找到了要插入的位置 --> 将cur插入进去
		cur = new Node(kv);
		if (cur->_kv.first < parent->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;

		//因为是三叉链，所以cur的_parent指针还要指回去
		cur->_parent = parent;

		//走到这里，插入完成了。需要检查平衡因子，判断是否平衡，不平衡要进行旋转
		while (parent)
		{
			//插入的位置是左孩子，bf--;插入的位置是右孩子，bf++
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			//接下来要判断根据不同的平衡因子进行不同的更新的情况
			if (parent->_bf == 0)
			{
				break;  //如果是0， 就不用更新了
			}
			else if (parent->_bf == -1 || parent->_bf == 1)   //如果插入之后parent的平衡因子等于-1或者1，说明还要向上调整
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//如果平衡因子走到这里，说明要发生旋转了：左旋，右旋，双旋。
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					//这种情况是左单旋，为什么？
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					//左边高，还要往左边插入，所以要发生右单旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//父节点右边高，当前节点左边高  --> 右左双旋
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//父节点左边高，当前节点右边高  --> 左右双旋
					RotateLR(parent);
				}
				else
				{
					assert("平衡因子出错");
				}
				break;
			}
			else
			{
				assert("平衡因子出错");
			}
		}
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		//1.把curleft给parent的right  --> parent的_right指向curleft
		parent->_right = curleft;

		//判断curleft是否为空，如果不为空，就curleft的父节点指回去
		if (curleft)
		{
			curleft->_parent = parent;
		}

		//2.parent的right给cur的left  --> cur的_left指向parent
		cur->_left = parent;

		//3.判断parent是不是当前的根节点,如果是，cur的_parent就为空。如果不是，cur的_parent还要指向ppnode
		Node* ppnode = parent->_parent;

		//4.parent还要往回指，因为是三叉链
		parent->_parent = cur;

		if (parent == _root)  //如果是根节点
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			//如果不是根节点，就要判断是ppnode的左孩子还是右孩子
			if (ppnode->_left == parent)
				ppnode->_left = cur;
			else
				ppnode->_right = cur;

			//往回指
			cur->_parent = ppnode;
		}

		//更新平衡因子
		parent->_bf = cur->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;

		//1.让parent的左指向cur的右
		parent->_left = curright;

		if (curright)
		{
			//第一次往回指
			curright->_parent = parent;
		}

		//找到parent的父节点
		Node* ppnode = parent->_parent;
		//2.cur的右指向parent
		cur->_right = parent;

		//第二次往回指
		parent->_parent = cur;

		if (parent == _root)
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			parent->_parent = cur;
			if (ppnode->_left == parent)
				ppnode->_left = cur;
			else
				ppnode->_right = cur;

			//第三次往回指
			cur->_parent = ppnode;
		}

		//更新平衡因子
		cur->_bf = parent->_bf = 0;
	}
	
	//左右双旋
	void RotateLR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		int bf = curright->_bf;

		RotateL(cur);
		RotateR(parent);

		//根据不同的情况修改平衡因子
		if (bf == 0)
		{
			cur->_bf = 0;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (bf == 1)   //说明左边低，右边高
		{
			parent->_bf = 0;
			cur->_bf = -1;
			curright->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			cur->_bf = 0;
			curright->_bf = 0;
		}
		else
		{
			assert("RotateLR false");
		}
	}

	void RotateRL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		int bf = curleft->_bf;   //提前保存下来

		RotateR(cur);
		RotateL(parent);

		if (bf == 0)
		{
			cur->_bf = 0;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else if (bf == 1)  //说明插入的位置是curleft的右边
		{
			parent->_bf = -1;
			cur->_bf = 0;
			curleft->_bf = 0;
		}
		else if (bf == -1)  //插入的位置是curleft的左边
		{
			parent->_bf = 0;
			cur->_bf = 1;
			curleft->_bf = 0;
		}
		else
		{
			assert("RotateRL false");
		}
	}

	//bool Erase(const pair<K, V>& key)
	//{

	//}
	int Height()
	{
		return Height(_root);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}

	bool IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int leftHight = Height(root->_left);
		int rightHight = Height(root->_right);

		if (rightHight - leftHight != root->_bf)
		{
			cout << "平衡因子异常:" << root->_kv.first << "->" << root->_bf << endl;
			return false;
		}

		return abs(rightHight - leftHight) < 2
			&& IsBalance(root->_left)
			&& IsBalance(root->_right);
	}

	void Inorder()
	{
		_Inorder(_root);
	}

private:
	void _Inorder(Node* cur)
	{
		if (cur == nullptr)
			return;
		
		_Inorder(cur->_left);
		cout << cur->_kv.first << " : " << cur->_kv.second << " : " << cur->_bf << endl;
		_Inorder(cur->_right);
	}
private:
	Node* _root = nullptr;
};
