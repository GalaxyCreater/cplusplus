/*
https://www.nowcoder.com/tutorial/93/a34ed23d58b84da3a707c70371f59c21
*/
#include <memory>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "huawei/test.h"
#include "tencent/lizi.h"
#include "tencent/tc.h"
#include "tencent/test.h"

void TestConst1()
{
	char a[] = "123";
	cout << (void *)a << endl
		 << endl;
}

void TestConst2()
{
	const char *b = "123"; // 在常量区

	char c1[] = "123";		 // 在栈上
	const char c2[] = "123"; //在栈上的，但是编译器可能会做某些优化，将其放到常量区

	cout << (void *)b << endl;
	cout << (void *)c1 << endl;
	cout << (void *)c2 << endl;
}

void TestMap()
{
	map<string, int> m;
	m.insert(make_pair("a", 1));
	m.insert(make_pair("b", 2));
	m.insert(make_pair("c", 3));
	for (map<string, int>::iterator i = m.begin(); i != m.end(); i++)
	{
		if (i->second == 2)
		{
			i = m.erase(i);
		}
		printf("%s %d\n", i->first.c_str(), i->second);
	}
}

// n个整数的无序数组，找到每个元素后面比它大的第一个数，要求时间复杂度为O(N)
vector<int> findMax()
{
	int lst[] = {2, 1, 4, 6, 3, 5};
	vector<int> num(lst, lst + 5);
	if (num.size() == 0)
		return num;
	vector<int> res(num.size());
	int i = 0;
	stack<int> s;
	while (i < num.size())
	{

		if (s.empty() || num[s.top()] >= num[i]) // 遍历下去,小于当前栈顶的,放入
		{
			s.push(i++);
		}
		else
		{
			res[s.top()] = num[i]; // 遍历下去,大于当前栈顶的,出栈,并记录
			s.pop();
		}
	}
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << endl;
	return res;
}

int main()
{
	//TestLru();
	SolutionStr s;
	string str("abb");
	vector<string> vs = s.permutation(str);
	// for (auto i : vs)
	// {
	// 	cout << i << endl;
	// }
	cout << "len:" << vs.size() << endl;
	//s.perm2(str);
	return 0;
}