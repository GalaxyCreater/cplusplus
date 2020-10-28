
/*
shared_ptr 实现
*/

#include <stdio.h>
#include <iostream>
#include <utility> // std::swap
using namespace std;

class RefCount
{
public:
	RefCount() { m_cnt = 0; }
	void AddCount()
	{
		++m_cnt;
	}

	int DelCount()
	{
		return --m_cnt;
	}

	int GetCount() const
	{
		return m_cnt;
	}

private:
	int m_cnt;
};

template <typename T>
class MySharedPtr
{
	// 模板的各个实例间并不天然就有 friend 关系，因而不能互访私有成员 m_val 和 m_ref, 当用到对应模板时,会编译错误
	template <typename U>
	friend class MySharedPtr;

public:
	MySharedPtr(T *ptr = nullptr)
	{
		m_val = ptr;
		if (ptr != NULL)
		{
			m_ref.AddCount();
		}
	}

	~MySharedPtr()
	{
		if (m_val)
		{
			if (m_ref.DelCount())
			{
				delete m_val;
				m_val = nullptr;
			}
		}
	}

	// 拷贝构造
	template <typename U>
	MySharedPtr(MySharedPtr<U> rhs)
	{
		m_val = rhs.m_val;
		if (m_val != NULL)
		{
			rhs.m_ref.AddCount();
			m_ref = rhs.m_ref;
		}
	}

	// 移动构造函数
	template <typename U>
	MySharedPtr(MySharedPtr<U> &&rhs)
	{
		m_val = rhs.m_val;
		if (m_val != NULL)
		{
			m_ref = rhs.m_ref;
			rhs.m_val = nullptr;
		}
	}

	// 复制操作符
	template <typename U>
	MySharedPtr &operator=(MySharedPtr<U> rhs)
	{
		m_val = rhs.m_val;
		if (m_val != NULL)
		{
			m_ref = rhs.m_ref;
			rhs.m_val = nullptr;
		}

		return *this;
	}

public:
	// 指针通用操作符
	T &operator*() { return *m_val; }
	T *operator->() { return m_val; }
	operator bool() { return m_val; }

	// 获取引用计数
	long use_count() const
	{
		if (m_val)
		{
			return m_ref.GetCount();
		}

		return 0;
	}

private:
	void swap(MySharedPtr &rhs)
	{
		using std::swap;
		swap(m_val, rhs.m_val);
		swap(m_ref, rhs.m_ref);
	}

	RefCount m_ref;
	T *m_val;
};

class shape
{
public:
	virtual ~shape() {}
};

class circle : public shape
{
public:
	~circle() { puts("~circle()"); }
};

int main()
{
	{
		MySharedPtr<circle> ptr1(new circle());
		printf("use count of ptr1 is %ld\n",
			   ptr1.use_count());

		MySharedPtr<shape> ptr2;
		printf("use count of ptr2 was %ld\n",
			   ptr2.use_count());

		ptr2 = ptr1; // 如果没加friend class,到这行时会报错
		printf("use count of ptr2 is now %ld\n", ptr2.use_count());
		if (ptr1)
		{
			puts("ptr1 is not empty");
		}
	}
	return 0;
}