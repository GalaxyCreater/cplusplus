#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <string.h>

using namespace std;

vector<string> resLst;

void Deep(stack<int> st, deque<int> dq, vector<string> res)
{
	if (st.empty() && dq.empty())
	{
		string s = "";
		for (size_t i = 0; i < res.size(); i++)
		{
			s += res[i];
			if (i != res.size() - 1)
			{
				s = s + " ";
			}
		}

		return;
	}

	if (!dq.empty()) // 还有火车可以进站
	{
		int tmp = dq.front();
		dq.pop_front();
		st.push(tmp); // 进站
		Deep(st, dq, res);
	}

	if (!st.empty()) // 还有火车可以出站
	{
		int tmp = st.top();
		st.pop();

		res.push_back(to_string(tmp));
		Deep(st, dq, res);
	}
}

bool comp(const string &a, const string &b)
{
	return a > b;
}

int Test()
{
	int cnt = 0;

	resLst.clear();
	while (cin >> cnt)
	{
		deque<int> dq;
		for (size_t i = 0; i < cnt; i++)
		{
			int tmp;
			cin >> tmp;
			dq.push_back(tmp);
		}

		for (size_t i = 1; i <= 3; i++)
		{

			dq.push_back(i);
		}

		if (dq.empty())
		{
			continue;
		}

		vector<string> res;
		stack<int> st;
		res.reserve(cnt);
		Deep(st, dq, res);
		::sort(resLst.begin(), resLst.end(), comp);
		for (size_t i = 0; i < resLst.size(); i++)
		{
			printf("%s\n", resLst[i].c_str());
		}
	}

	return 0;
}

void T()
{
	int l[] = {6, 1, 5, 3, 2, 7, 4};
	int len = sizeof(l) / sizeof(l[0]);
	deque<int> dq;
	for (size_t i = 0; i < len; i++)
	{
		dq.push_back(l[i]);
	}

	int cnt = dq.size();
	vector<string> res;
	stack<int> st;
	res.reserve(cnt);
	Deep(st, dq, res);
	::sort(resLst.begin(), resLst.end(), comp);
	for (size_t i = 0; i < resLst.size(); i++)
	{
		printf("%s\n", resLst[i].c_str());
	}
}

static void Sta()
{
	cout << "static fun" << endl;
}

static int g_a = 111;