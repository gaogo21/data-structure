#pragma once
#include<iostream>

using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::endl;

namespace zyy
{
	template<class T>
	struct BSTreeNode
	{
		BSTreeNode<T>* _left;
		BSTreeNode<T>* _right;
		T _data;


		//���캯��
		BSTreeNode(const T& x)
			:_left(nullptr)
			,_right(nullptr)
			,_data(x)
		{}

	};


	template <class T>
	class BSTree
	{
	public:
		typedef BSTreeNode<T> Node;
		//Ĭ�Ϲ���
		BSTree()
			:_root(nullptr)
		{}

		//��������
		BSTree(const BSTree<T>& t)
		{
			_root = copy(t._root);
		}

		BSTree<T>& operator=(BSTree<T> t)
		{
			std::swap(_root, t._root);
			return *this;
		}

		~BSTree()
		{
			Destory(_root);
		}

		bool Insert(const T& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			//��Ϊ�գ�Ҫ�ҵ��ܲ����λ��
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//��ǰ�ڵ��keyС��key���ұ���
				if (cur->_data < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_data > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//�ߵ�����˵����һ����ͬ�ĵ�����
					return false;
				}
			}

			//�ߵ����˵���ҵ����ʵĲ���λ����
				//Ҫ�жϲ��뵽��ǰcur����߻����ұ�
			cur = new Node(key);
			if (parent->_data < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}

			return true;
		}

		bool Find(const T& key) const
		{
			if (_root == nullptr)
				return false;
			
			Node* cur = _root;
			while (cur)
			{
				//key�����ұ���
				if (cur->_data < key)
				{
					cur = cur->_right;
				}
				else if (cur->_data > key)
				{
					cur = cur->_left;
				}
				else
				{
					return true;
				}
			}

			return false;
		}

		bool Erase(const T& key)
		{
			if (_root == nullptr)
				return false;

			//�����������û�к��� | ��һ������ | ����������
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//1.�ҵ�key
				if (cur->_data < key)  //������
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_data > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//�ߵ�����˵���ҵ�ֵΪkey�Ľ����
					if (cur->_left == nullptr)
					{
						//�ж��ǲ��Ǹ��ڵ�
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							//�ж�cur��parent�����ӻ����Һ���
							if (parent->_left == cur)
							{
								//��parent�ӹ�cur���ҽڵ�->��Ϊ��Ϊ��
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}
					}
					else if (cur->_right == nullptr)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							//�ж�cur��parent�����ӻ����Һ���
							if (parent->_left == cur)
							{
								//��parent�ӹ�cur����ڵ�->��Ϊ��Ϊ��
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}
					}
					else
					{
						//���Ҷ���Ϊ��
						//���滻��㣬��ߵ�����Ԫ�ػ����ұߵ���С��Ԫ��
						Node* parent = cur;
						Node* leftMax = cur->_left;
						while (leftMax->_right)
						{
							parent = leftMax;
							leftMax = leftMax->_right;
						}

						//�ߵ����˵���Ѿ��ߵ���ߵ����Ԫ����
						std::swap(leftMax->_data, cur->_data);  //����leftMax��cur

						//�ж���parent�����ӻ����Һ���
						if (parent->_left == leftMax)
						{
							parent->_left = leftMax->_left;   //������ΪleftMax����ߵ����Ԫ�أ����������Һ�����
						}
						else
						{
							parent->_right = leftMax->_right;
						}

						cur = leftMax;
					}

					delete cur;
					return true;
				}
			}
			return false;
		}

		void Inorder()
		{
			return _Inorder(_root);
		}
	private:

		//�������
		void _Inorder(Node* root)
		{
			if (root == nullptr)
				return;
			
			_Inorder(root->_left);
			cout << root->_data << " ";
			_Inorder(root->_right);
		}

		Node* copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			
			Node* copyroot = new Node(root->_data);
			copyroot->_left = copy(root->_left);
			copyroot->_right = copy(root->_right);

			return copyroot;
		}

		void Destory(Node*& root)
		{
			if (root == nullptr)
				return;
			
			Destory(root->_left);
			Destory(root->_right);
			
			delete root;
			root == nullptr;
		}
		Node* _root;
	};
};