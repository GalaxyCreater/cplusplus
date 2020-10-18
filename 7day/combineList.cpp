#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

typedef list<int> ListInt;
typedef unordered_map<int, int> MapInt;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int GetMin(vector<ListNode *> &lists)
{
    int minIdx = -1;
    for (int i = 0; i < lists.size(); i++)
    {
        if (lists[i] == nullptr)
        {
            continue;
        }

        if (minIdx == -1)
        {
            minIdx = i;
        }
        else
        {
            if (lists[i]->val < lists[minIdx]->val)
            {
                minIdx = i;
            }
        }
    }

    return minIdx;
}

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    ListNode *res = nullptr;
    while (1)
    {
        int nullCnt = 0;
        int minIdx = GetMin(lists);
        if (-1 == minIdx)
        {
            return res;
        }

        if (res == nullptr)
        {
            res = lists[minIdx];
        }
        else
        {
            res->next = lists[minIdx];
            res = res->next;
        }
    }

    return res;
}

int main()
{

    return 0;
}
