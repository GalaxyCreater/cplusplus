/*
c++11实现的单例模式
*/
#include <mutex>
#include <iostream>
using std::cout;
using std::endl;
using std::lock_guard;
using std::mutex;
using std::string;

struct Item2
{
	int v;
	string name;

	Item2(int i, string s)
	{
		v = i + 1000;
		name = s;
	}
};

struct Item
{
	int v;
	string name;

	Item(int i, string s)
	{
		v = i;
		name = s;
	}
};

// 懒汉模式实现:使用到的时候才创建
template <typename T>
class SingletonOld
{
public:
	template <typename... Args>
	static T *getInstance(Args &&... args)
	{
		if (obj_ == nullptr) // 防止创建后,每次取都要锁一下
		{
			lock_guard<mutex> lck(lock_);
			if (obj_ == nullptr)
				obj_ = new T(std::forward<Args>(args)...);
		}
		return obj_;
	}
	SingletonOld(SingletonOld &rhs) = delete;
	SingletonOld(const SingletonOld &rhs) = delete;
	SingletonOld &operator=(SingletonOld &rhs) = delete;
	SingletonOld &operator=(const SingletonOld &rhs) = delete;

private:
	SingletonOld();
	static mutex lock_;
	static T *obj_;
};

template <typename T>
mutex SingletonOld<T>::lock_;

template <typename T>
T *SingletonOld<T>::obj_ = nullptr;

// 智能指针 + call_once
// td::call_once:可以保证多个线程对该函数只调用一次。也可用在解决线程安全的单例模式
template <typename C>
class SingletonNew
{
public:
	SingletonNew(SingletonNew &&) = delete;
	SingletonNew(const SingletonNew &) = delete;
	SingletonNew &operator=(SingletonNew &&) = delete;
	SingletonNew &operator=(const SingletonNew &) = delete;

private:
	SingletonNew()
	{
	}
	virtual ~SingletonNew()
	{
	}

public:
	template <typename... Args>
	static std::shared_ptr<C> getInstance(Args &&... args)
	{
		static std::once_flag oc;
		std::call_once(oc, [&] {
			instance = std::make_shared<C>(std::forward<Args>(args)...);
		});
		return instance;
	}

private:
	static std::shared_ptr<C> instance;
};

template <typename C>
std::shared_ptr<C> SingletonNew<C>::instance = nullptr;

int main()
{

	Item *item = SingletonOld<Item>::getInstance(1, "aa");
	cout << item->name << item->v << endl;

	Item2 *item2 = SingletonOld<Item2>::getInstance(1, "aa");
	cout << item2->name << item2->v << endl;

	auto i = SingletonNew<Item>::getInstance(2, "xx");
	cout << i->name << i->v << endl;

	auto i2 = SingletonNew<Item2>::getInstance(1, "xx");
	cout << i2->name << i2->v << endl;
	return 0;
}