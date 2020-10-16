/*
工厂方法: 更加不同类型,创建不同工厂,再用对应的工厂,创建对应的对象
*/

#include <memory>
#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
using namespace std;

class Obj
{
public:
	Obj(const string &n) : name(n) {}
	void Print()
	{
		cout << name << endl;
	}

private:
	string name;
};

class ObjA : public Obj
{
public:
	ObjA(const string &n) : Obj(n + ":ObjA") {}
};

class ObjB : public Obj
{
public:
	ObjB(const string &n) : Obj(n + ":ObjB")
	{
	}
};

class FactoryInterface
{
public:
	virtual Obj *Create() = 0;
};

class FactoryA : public FactoryInterface
{
public:
	Obj *Create()
	{
		return new ObjA("");
	}
};

class FactoryB : public FactoryInterface
{
public:
	Obj *Create()
	{
		return new ObjB("");
	}
};

// 用于不同类型获取工厂
class FactoryMap
{
	typedef unordered_map<string, FactoryInterface *> MapType;

public:
	static FactoryMap &GetInstance()
	{
		static FactoryMap m;
		return m;
	}

	FactoryMap()
	{
		// 预先创建好工厂
		factoryMap["t1"] = new FactoryA();
		factoryMap["t2"] = new FactoryB();
	}

	FactoryInterface *GetFactory(string name)
	{
		MapType::iterator itr = factoryMap.find(name);
		if (itr == factoryMap.end())
		{
			cout << "no factory type:" << name << endl;
			return NULL;
		}

		return itr->second;
	}

private:
	static MapType factoryMap;
};
FactoryMap::MapType FactoryMap::factoryMap = FactoryMap::MapType(); // 静态成员初始化方式

int main()
{
	FactoryInterface *factory = FactoryMap::GetInstance().GetFactory("t2");
	if (NULL == factory)
	{
		return -1;
	}
	Obj *obj = factory->Create();
	obj->Print();
}