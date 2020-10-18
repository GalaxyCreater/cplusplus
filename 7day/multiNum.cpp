#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;

/*
多数元素
    给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。
*/

// 方法1
int majorityElement1(vector<int> &nums)
{
    MapInt s;
    for (int i = 0; i < nums.size(); i++)
    {
        if (s.find(nums[i]) != s.end())
        {
            s[nums[i]] += 1;
        }
        else
        {
            s[nums[i]] = 1;
        }
        if (s[nums[i]] > nums.size() / 2)
        {
            return nums[i];
        }
    }

    return 0;
}

int majorityElement2(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
}

int main()
{

    return 0;
}
