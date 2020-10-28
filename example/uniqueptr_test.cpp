/*
unique_ptr 实现
*/

#include <cmath>
#include <iostream>
#include <stdio.h>

using namespace std;

struct Base
{
	int v;
};

class Derive : public Base
{
};

template <typename T>
class MyUniquePtr
{
public:
	// 让使用起来更像指针
	T *operator->() const { return m_v; }
	T &operator*() const { return *m_v; }
	operator bool() const { return m_v; }

public:
	explicit MyUniquePtr(T *t) // 禁用隐式类型转换
	{
		m_v = t;
	}

	MyUniquePtr(MyUniquePtr &&rhs)
	{
		cout << "move consturct" << endl;
		m_v = rhs.release();
	}

	/*
	处理MyUniquePtr<Derive>无法转换成MyUniquePtr<Base>的问题
		MyUniquePtr<Derive> d(new Derive());
		MyUniquePtr<Base> ptr(std::move(d));
	*/
	template <typename U>
	MyUniquePtr(MyUniquePtr<U> &&rhs)
	{
		cout << "template move consturct" << endl;
		m_v = rhs.release();
	}

	MyUniquePtr &operator=(MyUniquePtr rhs)
	{
		cout << "operator=" << endl;
		rhs.swap(*this);
		return *this;
	}

	~MyUniquePtr()
	{
		if (m_v != NULL)
		{
			delete m_v;
			m_v = NULL;
		}
	}
	T *release()
	{
		T *ptr = m_v;
		m_v = nullptr;
		return ptr;
	}
	void swap(MyUniquePtr &rhs)
	{
		using std::swap;
		swap(m_v, rhs.m_v);
	}

private:
	T *m_v;
};

int main()
{
	MyUniquePtr<int> s(new int(11));   // 左值
	MyUniquePtr<int> p = std::move(s); // 或MyUniquePtr<int> p(std::move(s))
	// MyUniquePtr<int> p = s; 编译报错,因为定义了移动构造函数,所有其他构造函数自动被禁用
	// MyUniquePtr<int> p(s);
	cout << *p << endl;
	//cout << "----" << *s << endl; // 崩溃

	MyUniquePtr<Derive> d(new Derive());
	MyUniquePtr<Base> ptr(std::move(d));
	cout << ptr->v << endl;
	return 0;
}