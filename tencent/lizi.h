#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
#include <string.h>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

typedef vector<int> VecInt;
typedef pair<int, int> PairInt;

struct LruNode
{
	int key;
	int val;

	LruNode(int k, int v) : key(k), val(v) {}
};

class LRUCache
{
	int m_capacity;

public:
	LRUCache(int capacity)
	{
		m_capacity = capacity;
	}

	int get(int key)
	{
		MapType::iterator itr = m.find(key);
		if (itr == m.end())
		{
			return -1;
		}

		l.push_front(*(itr->second));
		delete *(itr->second);
		l.erase(itr->second);

		return (*itr->second)->val;
	}

	void put(int key, int value)
	{
		if (m.find(key) != m.end())
		{
			return;
		}

		LruNode *n = new LruNode(key, value);
		l.push_front(n);
		m[key] = l.begin();
		if (l.size() > m_capacity)
		{
			m.erase(l.back()->key);
			delete l.back();
			l.pop_back();
		}
	}

	void print()
	{
		for (ListType::iterator i = l.begin(); i != l.end(); i++)
		{
			cout << (*i)->key << " " << (*i)->val << endl;
		}
	}

private:
	typedef list<LruNode *> ListType;
	typedef map<int, ListType::iterator> MapType;

	ListType l;
	MapType m;
};

void TestLru()
{
	LRUCache l(4);
	l.put(1, 1);
	l.put(2, 2);

	l.put(3, 3);
	l.put(4, 4);

	l.print();
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
public:
	TreeNode *invertTree(TreeNode *root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		TreeNode *node = root->left;
		root->left = root->right;
		root->right = node;

		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};

TreeNode *invertTree(TreeNode *root)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	TreeNode *left = invertTree(root->left);
	TreeNode *right = invertTree(root->right);
	root->left = right;
	root->right = left;
	return root;
};