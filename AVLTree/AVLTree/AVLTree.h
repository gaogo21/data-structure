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


	//newһ��AVLTreeNode�ڵ��ʱ��ͻ����������캯��
	// ����������������kv
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
		//�����Ĳ���
		//...����ƽ��
		//��������ߣ����ڵ��ƽ������-- | �������ұߣ����ڵ��ƽ������++  �����Ľڵ��Ӱ�쵽��������
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
				assert("������ͬ�Ľڵ�");
			}
		}

		//�ߵ�����ҵ���Ҫ�����λ�� --> ��cur�����ȥ
		cur = new Node(kv);
		if (cur->_kv.first < parent->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;

		//��Ϊ��������������cur��_parentָ�뻹Ҫָ��ȥ
		cur->_parent = parent;

		//�ߵ������������ˡ���Ҫ���ƽ�����ӣ��ж��Ƿ�ƽ�⣬��ƽ��Ҫ������ת
		while (parent)
		{
			//�����λ�������ӣ�bf--;�����λ�����Һ��ӣ�bf++
			if (cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;

			//������Ҫ�жϸ��ݲ�ͬ��ƽ�����ӽ��в�ͬ�ĸ��µ����
			if (parent->_bf == 0)
			{
				break;  //�����0�� �Ͳ��ø�����
			}
			else if (parent->_bf == -1 || parent->_bf == 1)   //�������֮��parent��ƽ�����ӵ���-1����1��˵����Ҫ���ϵ���
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//���ƽ�������ߵ����˵��Ҫ������ת�ˣ�������������˫����
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					//���������������Ϊʲô��
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					//��߸ߣ���Ҫ����߲��룬����Ҫ�����ҵ���
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//���ڵ��ұ߸ߣ���ǰ�ڵ���߸�  --> ����˫��
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//���ڵ���߸ߣ���ǰ�ڵ��ұ߸�  --> ����˫��
					RotateLR(parent);
				}
				else
				{
					assert("ƽ�����ӳ���");
				}
				break;
			}
			else
			{
				assert("ƽ�����ӳ���");
			}
		}
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;

		//1.��curleft��parent��right  --> parent��_rightָ��curleft
		parent->_right = curleft;

		//�ж�curleft�Ƿ�Ϊ�գ������Ϊ�գ���curleft�ĸ��ڵ�ָ��ȥ
		if (curleft)
		{
			curleft->_parent = parent;
		}

		//2.parent��right��cur��left  --> cur��_leftָ��parent
		cur->_left = parent;

		//3.�ж�parent�ǲ��ǵ�ǰ�ĸ��ڵ�,����ǣ�cur��_parent��Ϊ�ա�������ǣ�cur��_parent��Ҫָ��ppnode
		Node* ppnode = parent->_parent;

		//4.parent��Ҫ����ָ����Ϊ��������
		parent->_parent = cur;

		if (parent == _root)  //����Ǹ��ڵ�
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			//������Ǹ��ڵ㣬��Ҫ�ж���ppnode�����ӻ����Һ���
			if (ppnode->_left == parent)
				ppnode->_left = cur;
			else
				ppnode->_right = cur;

			//����ָ
			cur->_parent = ppnode;
		}

		//����ƽ������
		parent->_bf = cur->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;

		//1.��parent����ָ��cur����
		parent->_left = curright;

		if (curright)
		{
			//��һ������ָ
			curright->_parent = parent;
		}

		//�ҵ�parent�ĸ��ڵ�
		Node* ppnode = parent->_parent;
		//2.cur����ָ��parent
		cur->_right = parent;

		//�ڶ�������ָ
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

			//����������ָ
			cur->_parent = ppnode;
		}

		//����ƽ������
		cur->_bf = parent->_bf = 0;
	}
	
	//����˫��
	void RotateLR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		int bf = curright->_bf;

		RotateL(cur);
		RotateR(parent);

		//���ݲ�ͬ������޸�ƽ������
		if (bf == 0)
		{
			cur->_bf = 0;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (bf == 1)   //˵����ߵͣ��ұ߸�
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
		int bf = curleft->_bf;   //��ǰ��������

		RotateR(cur);
		RotateL(parent);

		if (bf == 0)
		{
			cur->_bf = 0;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else if (bf == 1)  //˵�������λ����curleft���ұ�
		{
			parent->_bf = -1;
			cur->_bf = 0;
			curleft->_bf = 0;
		}
		else if (bf == -1)  //�����λ����curleft�����
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
			cout << "ƽ�������쳣:" << root->_kv.first << "->" << root->_bf << endl;
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
