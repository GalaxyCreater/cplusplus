
/*
全排列字符串
如:abcd
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class SolutionStr
{
	vector<string> res;

public:
	void exchange(string &s, int l, int r)
	{
		char tmp = s[l];
		s[l] = s[r];
		s[r] = tmp;
	}
	void perm(int idx, string &comb)
	{
		if (idx >= comb.length())
		{
			res.push_back(comb);
			return;
		}
		set<char> st;
		for (size_t i = idx; i < comb.length(); i++) // 从idx位开始,不停交换字符
		{
			if (st.find(comb[i]) != st.end()) //防止出现 abb 这样的字符串,重复添加
			{
				continue;
			}
			st.insert(comb[i]);

			exchange(comb, idx, i);
			perm(idx + 1, comb);	// idx位后的字符,逐个放到i位置,求他们后面的组合
			exchange(comb, idx, i); // 还原
		}
	}

	void _perm2(string res, string str, int idx, vector<string> &vecList, set<int> &st)
	{
		if (idx >= str.length())
		{
			vecList.push_back(res);
			return;
		}

		for (int i = 0; i < str.size(); i++) // 用每个字符填充第idx位
		{
			if (st.find(i) != st.end())
			{
				continue;
			}
			else
			{
				st.insert(i);
			}

			res[idx] = str[i];
			_perm2(res, str, idx + 1, vecList, st); // 填充下一位
			st.erase(i);							// 还原已访问集合
		}
	}

	void perm2(string s)
	{
		vector<string> lst;
		string res;
		res.resize(s.size());
		set<int> st;
		_perm2(res, s, 0, lst, st); //// 从第一个位置填充
		cout << lst.size() << endl;

		// for (auto i : lst)
		// {
		// 	cout << i << " ";
		// }
	}

	vector<string> permutation(string s)
	{
		string comb = s;
		perm(0, comb);
		return res;
	}
};
