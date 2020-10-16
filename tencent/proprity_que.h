#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution
{
	typedef greater<int> GreaterType;

	typedef vector<int> VecInt;

public:
	int findKthLargest(vector<int> &nums, int k)
	{
		priority_queue<int, VecInt, GreaterType> que;
		for (auto i : nums)
		{
			que.push(i);
			if (que.size() > k)
			{
				que.pop();
			}
		}

		int val = 0;
		for (size_t i = 1; i < k; i++)
		{
			val = que.top();
			que.pop();
		}
		return val;
	}
};
