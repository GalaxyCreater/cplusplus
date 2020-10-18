#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;
typedef vector<int> VecInt;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        MapInt m;
        VecInt res;
        for (int i = 0; i < nums.size(); i++)
        {

            MapInt::iterator sec = m.find(target - nums[i]);
            if (sec != m.end())
            {
                res.push_back(i);
                res.push_back(sec->second);
                return res;
            }
            if (m.find(nums[i]) == m.end())
            {
                m[nums[i]] = i;
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    int a[] = {3, 2, 4};
    VecInt v(a, a + sizeof(a) / sizeof(a[0]));

    VecInt res = s.twoSum(v, 6);
    for (auto i : res)
    {
        cout << i << endl;
    }

    return 0;
}