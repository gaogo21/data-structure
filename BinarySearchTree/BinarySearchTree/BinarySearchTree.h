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


		//构造函数
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
		//默认构造
		BSTree()
			:_root(nullptr)
		{}

		//拷贝构造
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

			//不为空，要找到能插入的位置
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//当前节点比key小，key往右边走
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
					//走到这里说明有一个相同的的数了
					return false;
				}
			}

			//走到这里，说明找到合适的插入位置了
				//要判断插入到当前cur的左边还是右边
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
				//key大，往右边找
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

			//分三种情况，没有孩子 | 有一个孩子 | 有两个孩子
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				//1.找到key
				if (cur->_data < key)  //往右找
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
					//走到这里说明找到值为key的结点了
					if (cur->_left == nullptr)
					{
						//判断是不是根节点
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							//判断cur是parent的左孩子还是右孩子
							if (parent->_left == cur)
							{
								//让parent接管cur的右节点->因为左为空
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
							//判断cur是parent的左孩子还是右孩子
							if (parent->_left == cur)
							{
								//让parent接管cur的左节点->因为右为空
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
						//左右都不为空
						//找替换结点，左边的最大的元素或者右边的最小的元素
						Node* parent = cur;
						Node* leftMax = cur->_left;
						while (leftMax->_right)
						{
							parent = leftMax;
							leftMax = leftMax->_right;
						}

						//走到这里，说明已经走到左边的最大元素了
						std::swap(leftMax->_data, cur->_data);  //交换leftMax和cur

						//判断是parent的左孩子还是右孩子
						if (parent->_left == leftMax)
						{
							parent->_left = leftMax->_left;   //这是因为leftMax是左边的最大元素，不可能有右孩子了
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

		//中序遍历
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