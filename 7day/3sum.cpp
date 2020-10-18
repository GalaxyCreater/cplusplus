#include <iostream>
#include <list>
#include <vector>
using namespace std;
typedef vector<int> VecInt;
typedef list<int> ListInt;

/*
三数之和
*/
//方法1: 穷举方法
vector<VecInt> threeSum(vector<int> &nums)
{
    vector<VecInt> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }

        for (int j = i + 1; j < nums.size(); j++)
        {

            if (j > i + 1 && nums[j] == nums[j - 1]) // 不能和上一个元素相等
            {
                continue;
            }

            for (int k = j + 1; k < nums.size(); k++)
            {
                if (k > j + 1 && nums[k] == nums[k - 1]) // 不能和上一个元素相等
                {
                    continue;
                }

                if (nums[i] + nums[j] + nums[k] == 0)
                {
                    VecInt v;
                    v.push_back(nums[i]);
                    v.push_back(nums[j]);
                    v.push_back(nums[k]);
                    // v.push_back(i);
                    // v.push_back(j);
                    // v.push_back(k);
                    res.push_back(v);
                }
            }
        }
    }

    return res;
}

// 方法2:排序 + 双索引
vector<VecInt> threeSum2(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    vector<VecInt> res;
    int target = 0;
    for (int one = 0; one < nums.size(); one++)
    {
        if (one > 0 && nums[one] == nums[one - 1]) // 跳过第一个数所有重复的
        {
            continue;
        }

        int three = nums.size() - 1;
        int left = target - nums[one];
        for (int two = one + 1; two < nums.size(); two++)
        {
            if (two > one + 1 && nums[two] == nums[two - 1]) // 跳过第二个数所有重复的
            {
                continue;
            }

            while (three > two && nums[two] + nums[three] > left)
            {
                three--;
            }

            if (three == two) // 全部考察完
            {
                break;
            }

            if (left == (nums[two] + nums[three]))
            {
                VecInt v;
                v.push_back(nums[one]);
                v.push_back(nums[two]);
                v.push_back(nums[three]);
                res.push_back(v);
            }
        }
    }

    return res;
}

vector<VecInt> threeSum3(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<VecInt> ans;
    // 枚举 a
    for (int first = 0; first < n; ++first)
    {
        // 需要和上一次枚举的数不相同
        if (first > 0 && nums[first] == nums[first - 1])
        {
            continue;
        }
        // c 对应的指针初始指向数组的最右端
        int third = n - 1;
        int target = -nums[first];
        // 枚举 b
        for (int second = first + 1; second < n; ++second)
        {
            // 需要和上一次枚举的数不相同
            if (second > first + 1 && nums[second] == nums[second - 1])
            {
                continue;
            }
            // 需要保证 b 的指针在 c 的指针的左侧
            while (second < third && nums[second] + nums[third] > target)
            {
                --third;
            }
            // 如果指针重合，随着 b 后续的增加
            // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
            if (second == third)
            {
                break;
            }
            if (nums[second] + nums[third] == target)
            {
                VecInt v;
                v.push_back(nums[first]);
                v.push_back(nums[second]);
                v.push_back(nums[third]);
                ans.push_back(v);
            }
        }
    }
    return ans;
}

int main()
{
    int a[] = {-1, 0, 1, 2, -1, -4};
    //int a[] = {-1, -1, 2};
    VecInt v(a, a + sizeof(a) / sizeof(a[0]));
    auto res = threeSum2(v);
    for (int i = 0; i < res.size(); i++)
    {
        auto tmp = res[i];
        for (int j = 0; j < tmp.size(); j++)
        {
            cout << tmp[j] << ",";
        }
        cout << endl;
    }

    return 0;
}
