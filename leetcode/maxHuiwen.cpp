
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;
typedef vector<int> VecInt;

/*

*/
class Solution
{
public:
    string longestPalindrome(string c)
    {
        string s;
        s += ('#');
        for (size_t i = 0; i < c.length(); i++)
        {
            s += c[i];
            s += '#';
        }

        int max = 1;
        int l = -1, r = -1;
        string res;
        for (int i = 1; i < s.length(); i++)
        {
            l = i - 1, r = i + 1;
            int len = 1;
            while (1)
            {
                if (s[l] == s[r])
                {
                    len++;
                }
                else
                {
                    l++;
                    r--;
                    break;
                }
                if (l - 1 < 0 || r + 1 >= s.length())
                {
                    break;
                }
                l--;
                r++;
            }
            if (len > max)
            {
                max = len;
                res = s.substr(l, r - l + 1);
            }
        }

        if (l == -1)
        {
            return c.substr(0, 1);
        }

        string rr;
        for (int i = 0; i < res.size(); i++)
        {
            if (res[i] == '#')
            {
                continue;
            }
            rr += res[i];
        }

        return rr;
    }
};

int main()
{
    string a = "bb";
    Solution s;
    cout << s.longestPalindrome(a) << endl;
    ;
    return 0;
}
