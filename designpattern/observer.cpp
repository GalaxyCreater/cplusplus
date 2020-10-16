/*
观察者模式
*/

#include <iostream>
#include <set>
using namespace std;

class Observer
{
public:
	// 观察者接收消息
	virtual void update(string message) = 0;
};

class ObserverObj1 : public Observer
{

public:
	virtual void update(string message)
	{
		cout << "obj1 handle: " << message << endl;
	}
};

class ObserverObj2 : public Observer
{
public:
	virtual void update(string message)
	{
		cout << "obj2 handle: " << message << endl;
	}
};

// 主题接口
class SubjectBase
{
public:
	// 添加观察者
	virtual void regist(Observer *o) = 0;
	// 删除观察者
	virtual void remove(Observer *o) = 0;
	// 通知所有观察者
	virtual void notify(string message) = 0;
};

class SubjectImpl : public SubjectBase
{
	set<Observer *> observerSet;

public:
	virtual void regist(Observer *o)
	{
		observerSet.insert(o);
	}
	virtual void remove(Observer *o)
	{
		observerSet.erase(o);
	}
	virtual void notify(string message)
	{
		for (auto i : observerSet)
		{
			i->update(message);
		}
	}
};

int main()
{
	SubjectImpl sub;
	ObserverObj1 obj1;
	ObserverObj2 obj2;
	sub.regist(&obj1);
	sub.regist(&obj2);

	sub.notify("hello world");

	return 0;
}
