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
		//1.1Ĭ�Ϲ���
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}


		//1.2 n��ֵ���� -- ����ʹ��������������Ϊ��֪��Ҫ����Ķ�����ʲô���ͣ�
		vector(size_t n, const T& value = T())
		{
			resize(n, value);
		}

		//��ֹ���� �Ƿ��ļ��Ѱַ ����
		vector(int n, const T& value = T())
		{
			resize(n, value);
		}

		//1.3 �õ�������ʼ��
		template <class InputIterator>    //����ʹ��ģ���ԭ���ǿ����кܶ����͵ĵ�����,string,int, double��
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

		//1.4 ��������  -- ��v����ʼ��this
		//vector(const vector<T>& v)
		//{
		//	//ע�⣺����ʹ��memcpy,memcpy��ǳ����
		//	_start = new T[v.capacity()];   //����һ���µĿռ�
		//	for (size_t i = 0; i < v.size(); ++i)
		//	{
		//		_start[i] = v[i];
		//	}

		//	_finish = _start + v.size();
		//	_end_of_storage = _start + v.capacity();
		//}

		// ��������
		vector(const vector<T>& v)
		{
			_start = new T[v.capacity()]; //����һ�������v��С��ͬ�Ŀռ�
			memcpy(_start, v._start, sizeof(T) * v.size());//������v���е�����һ������������
			_finish = _start + v.size(); //������Ч���ݵ�β
			_end_of_storage = _start + v.capacity(); //����������β
		}

		//vector(const vector<T>& v)
		//{
		//	_start = v._start;
		//	_finish = _start + v.size(); //������Ч���ݵ�β
		//	_end_of_storage = _start + v.capacity(); //����������β
		//}

		//��ֵ��������غ���
		vector<T>& operator=(const vector<T>& v)
		{
			//��ֹ�Լ����Լ���ֵ
			if (this != &v)
			{
				//1.�ͷŵ�ԭ���Ŀռ�
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
		//������
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

		//2.��������
		//2.1β��
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

			//1.�ж������߼�
			if (_finish == _end_of_storage)
			{
				//1.1�����pos��_start��ƫ����
				int n = _start - pos;
				int newCapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapacity);
				//1.2������֮�����ƫ�����ҵ���pos��λ��
				pos = _start + n;
			}

			//2.��pos������������ƶ�
			auto end = _finish - 1;   //_finishָ��������һ��Ԫ�ص���һ��λ��
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			//3.��val���뵽vector��
			*pos = val;
			++_finish;

			//���ص�����
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
		//2.2 ���ݺ�������vector����������n
		void reserve(size_t n)
		{
			if (n <= capacity())
			{
				//�������κβ���
			}
			else
			{
				//�Ƚ�size()�����ݴ洢����
				int sz = size();
				//����������ǿ���һ��ռ䣬���ɵ����ݿ������¿ռ���
				T* tmp = new T[n];
				if (_start)
				{
					for (int i = 0; i < size(); ++i)
					{
						tmp[i] = _start[i];
					}
					//�ͷŵ���ǰ�Ŀռ�
					delete[] _start;
				}
				//��_startָ���¿��ٵĿռ�
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
				//1.����
				reserve(n);
				//2.�����ݲ��뵽vector��
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
