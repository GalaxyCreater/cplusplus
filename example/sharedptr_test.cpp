
/*
shared_ptr 实现
*/

#include <iostream>
#include <utility> // std::swap
#include <memory>
using namespace std;

class shared_count
{
public:
	shared_count() noexcept
		: count_(1) {}
	void add_count() noexcept
	{
		++count_;
	}
	long reduce_count() noexcept
	{
		return --count_;
	}
	long get_count() const noexcept
	{
		return count_;
	}

private:
	long count_;
};

template <typename T>
class smart_ptr
{
public:
	template <typename U>
	friend class smart_ptr; // 因为模板类型不一样typename U,所以要声明为友元类;  删了也能编译通过,为什么?

	explicit smart_ptr(T *ptr = nullptr)
		: ptr_(ptr)
	{
		if (ptr)
		{
			shared_count_ = new shared_count();
		}
	}
	~smart_ptr()
	{
		if (ptr_ && !shared_count_->reduce_count())
		{
			delete ptr_;
			delete shared_count_;
		}
	}

	smart_ptr(const smart_ptr &other)
	{
		ptr_ = other.ptr_;
		if (ptr_)
		{
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}
	template <typename U>
	smart_ptr(const smart_ptr<U> &other) noexcept
	{
		ptr_ = other.ptr_;
		if (ptr_)
		{
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	/*
	处理MyUniquePtr<Derive>无法转换成MyUniquePtr<Base>的问题
		MyUniquePtr<Derive> d(new Derive());
		MyUniquePtr<Base> ptr(std::move(d));
	*/
	template <typename U>
	smart_ptr(smart_ptr<U> &&other) noexcept
	{
		ptr_ = other.ptr_;
		if (ptr_)
		{
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
		}
	}

	template <typename U>
	smart_ptr(const smart_ptr<U> &other, T *ptr) noexcept
	{
		ptr_ = ptr;
		if (ptr_)
		{
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}
	smart_ptr &operator=(smart_ptr rhs) noexcept
	{
		rhs.swap(*this);
		return *this;
	}

	T *get() const noexcept
	{
		return ptr_;
	}
	long use_count() const noexcept
	{
		if (ptr_)
		{
			return shared_count_
				->get_count();
		}
		else
		{
			return 0;
		}
	}
	void swap(smart_ptr &rhs) noexcept
	{
		using std::swap;
		swap(ptr_, rhs.ptr_);
		swap(shared_count_,
			 rhs.shared_count_);
	}

	T &operator*() const noexcept
	{
		return *ptr_;
	}
	T *operator->() const noexcept
	{
		return ptr_;
	}
	operator bool() const noexcept
	{
		return ptr_;
	}

private:
	T *ptr_;
	shared_count *shared_count_;
};

template <typename T>
void swap(smart_ptr<T> &lhs,
		  smart_ptr<T> &rhs) noexcept
{
	lhs.swap(rhs);
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(
	const smart_ptr<U> &other) noexcept
{
	T *ptr = static_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(
	const smart_ptr<U> &other) noexcept
{
	T *ptr = reinterpret_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> const_pointer_cast(
	const smart_ptr<U> &other) noexcept
{
	T *ptr = const_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(
	const smart_ptr<U> &other) noexcept
{
	T *ptr = dynamic_cast<T *>(other.get());
	return smart_ptr<T>(other, ptr);
}

void Fun1(std::shared_ptr<int> ptr)
{
	cout << "refer count: " << ptr.use_count() << endl;
}

void Fun2(std::shared_ptr<int> &ptr)
{
	cout << "& refer count: " << ptr.use_count() << endl;
}

void Fun3(std::shared_ptr<int> &&ptr)
{
	cout << "&& refer count: " << ptr.use_count() << endl;
}

int main()
{
	std::shared_ptr<int> p(new int(10));
	cout << p.use_count() << endl;
	Fun1(p);
	Fun2(p);
	Fun3(std::move(p));
	return 0;
}