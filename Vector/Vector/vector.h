#pragma once
#include<iostream>
#include<assert.h>
using std::cout;
using std::cin;
using std::endl;

namespace zyy
{
	template<class T>
	class vector
	{
		typedef T* iterator;
		typedef const T* const_itertator;
	public:
		//1.1默认构造
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}


		//1.2 n个值构造 -- 这里使用匿名对象，是因为不知道要构造的对象是什么类型，
		vector(size_t n, const T& value = T())
		{
			resize(n, value);
		}

		//防止出现 非法的间接寻址 问题
		vector(int n, const T& value = T())
		{
			resize(n, value);
		}

		//1.3 用迭代器初始化
		template <class InputIterator>    //这里使用模板的原因是可能有很多类型的迭代器,string,int, double等
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//1.4 拷贝构造  -- 用v来初始化this
		//vector(const vector<T>& v)
		//{
		//	//注意：不能使用memcpy,memcpy是浅拷贝
		//	_start = new T[v.capacity()];   //开辟一块新的空间
		//	for (size_t i = 0; i < v.size(); ++i)
		//	{
		//		_start[i] = v[i];
		//	}

		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.capacity();
		//}

		// 拷贝构造
		vector(const vector<T>& v)
		{
			_start = new T[v.capacity()]; //开辟一块和容器v大小相同的空间
			memcpy(_start, v._start, sizeof(T) * v.size());//将容器v当中的数据一个个拷贝过来
			_finish = _start + v.size(); //容器有效数据的尾
			_end_of_storage = _start + v.capacity(); //整个容器的尾
		}

		//vector(const vector<T>& v)
		//{
		//	_start = v._start;
		//	_finish = _start + v.size(); //容器有效数据的尾
		//	_end_of_storage = _start + v.capacity(); //整个容器的尾
		//}

		//赋值运算符重载函数
		vector<T>& operator=(const vector<T>& v)
		{
			//防止自己给自己赋值
			if (this != &v)
			{
				//1.释放掉原来的空间
				delete[] _start;
				_start = new T[v.capacity()];

				for (int i = 0; i < v.size(); ++i)
				{
					_start[i] = v[i];
				}

				_finish = _start + v.size();
				_end_of_storage = _start + v.capacity();
			}

			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_end_of_storage = nullptr;
		}
		//迭代器
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_itertator begin() const
		{
			return _start;
		}

		const_itertator end() const
		{
			return _finish;
		}
		//operator[]
		T& operator[](size_t pos)
		{
			assert(pos < size());

			return _start[pos];
		}

		const T& operator[](size_t pos) const
		{
			assert(pos < size());

			return _start[pos];
		}

		//2.操作函数
		//2.1尾插
		void push_back(const T& val)
		{
			if (_finish == _end_of_storage)
			{
				int newCapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newCapacity);
			}

			*_finish = val;
			++_finish;
		}

		void pop_back()
		{
			assert(_finish >= _start);
			--_finish;
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);

			//1.判断扩容逻辑
			if (_finish == _end_of_storage)
			{
				//1.1计算出pos和_start的偏移量
				int n = _start - pos;
				int newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);
				//1.2扩容完之后根据偏移量找到新pos的位置
				pos = _start + n;
			}

			//2.将pos后的内容往后移动
			auto end = _finish - 1;   //_finish指向的是最后一个元素的下一个位置
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			//3.将val插入到vector中
			*pos = val;
			++_finish;

			//返回迭代器
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos <= _finish);

			auto it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}

			--_finish;

			return pos;
		}
		//2.2 扩容函数，将vector的容量扩大到n
		void reserve(size_t n)
		{
			if (n <= capacity())
			{
				//不进行任何操作
			}
			else
			{
				//先将size()的内容存储下来
				int sz = size();
				//这里的扩容是开辟一块空间，将旧的内容拷贝的新空间上
				T* tmp = new T[n];
				if (_start)
				{
					for (int i = 0; i < size(); ++i)
					{
						tmp[i] = _start[i];
					}
					//释放掉以前的空间
					delete[] _start;
				}
				//让_start指向新开辟的空间
				_start = tmp;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void resize(size_t n, const T& value = T())
		{
			if (n <= size())
			{
				_finish = _start + n;
			}
			else
			{
				//1.扩容
				reserve(n);
				//2.将内容插入到vector中
				while (_finish != _start + n)
				{
					*_finish = value;
					++_finish;
				}
			}
		}
		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		void print()
		{
			for (int i = 0; i < size(); ++i)
			{
				cout << _start[i] << " ";
			}
			cout << endl;
		}
	private:
		T* _start = nullptr;
		T* _finish = nullptr;
		T* _end_of_storage = nullptr;
	};
}
