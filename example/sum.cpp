
#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <string.h>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;
//using namespace stdext;
typedef vector<int> VecInt;
typedef unordered_map<int, int> IntMap;

/*
列出两数和的所有可能情况
*/
void GetAllTowSum(VecInt &vec, int total)
{
	for (int i = 0; i < vec.size(); i++)
	{
		int left = total - vec[i];
		for (int j = i; j < vec.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			if (left == vec[j])
			{
				printf("%d:%d  %d:%d\n", i, vec[i], j, vec[j]);
			}
		}
	}
}

/*
给定一个数字，在一组数字中，找出两个相加等于该数字的两个数。复杂度尽可能低
desc: 使用hash map查找,时间复杂度:O(n), 空间复杂度(O(n))
*/
void GetTwoSum(VecInt &vec, int total)
{
	//sort(vec.begin(), vec.end());
	IntMap m; // m可以换成2分查找方式
	for (int i = 0; i < vec.size(); i++)
	{
		m[vec[i]] = i;
	}

	for (int i = 0; i < vec.size(); i++)
	{
		IntMap::iterator itr = m.find(total - vec[i]);
		if (itr != m.end())
		{
			cout << i << " " << itr->second << endl;
			return;
		}
	}
}

/*
方法2:因为数组里的数,
	两两相加最小值是最大和次大的值,
	两两相加最小值是最小值和次小值,
	两两相加中位数是最大值和最小值的和,所以可以通过考察两两相加的和来找
*/
void GetTwoSum2(VecInt &vec, int total)
{
	sort(vec.begin(), vec.end());
	int maxIdx = vec.size() - 1;
	int minIdx = 0;

	while (1)
	{
		int tmp = vec[maxIdx] + vec[minIdx];
		if (tmp == total)
		{
			printf("%d:%d  %d:%d\n", minIdx, vec[minIdx], maxIdx, vec[maxIdx]);
			return;
		}

		if (tmp > total)
		{
			minIdx++;
		}
		else
		{
			maxIdx--;
		}

		if (minIdx >= vec.size() || maxIdx <= 0)
		{
			break;
		}
	}
}

int main()
{
	int a[] = {1,
			   5,
			   4,
			   5,
			   7,
			   3};
	VecInt vec(a, a + sizeof(a) / sizeof(a[0]));
	GetAllTowSum(vec, 8);
	GetTwoSum(vec, 8);
	GetTwoSum2(vec, 8);

	return 0;
}