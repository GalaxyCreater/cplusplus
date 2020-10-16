/*

*/
#include <memory>
#include <stdio.h>
#include <iostream>
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

class Obj1 : public Obj
{
public:
	Obj1(const string &n) : Obj(n + ":Obj1") {}
};

class Obj2 : public Obj
{
public:
	Obj2(const string &n) : Obj(n + ":Obj2")
	{
	}
};

class TypeFactory
{

public:
	static Obj *Create(const string &name)
	{
		if (name == "t1")
		{
			return new Obj1(name);
			/* code */
		}
		else if (name == "t2")
		{
			return new Obj2(name);
		}

		return NULL;
	}
};

int main()
{
	Obj *obj = TypeFactory::Create("t2");

	obj->Print();
}