#include <bits/stdc++.h>
#include "persistent_set.h"
#include "my_linked_ptr.h"

using namespace std;

int main()
{
	{
		persistent_set<int> p;
		p.insert(1);
		p.insert(3);
		p.insert(2);
		p.insert(4);
		persistent_set<int>::iterator it;
		it = p.end();
		for (int i = 0; i < 4; ++i)
		{
			--it;
			cout << *it << " ";
		}
		cout << "\n";
		++it;
		++it;
		cout << *it << endl;
		p.erase(it);
		it = p.end();
		for (int i = 0; i < 3; ++i)
		{
			--it;
			cout << *it << " ";
		}
		cout << "\n";
		persistent_set<int> p2(p);
		p2.insert(3);
		it = p2.end();
		for (int i = 0; i < 4; ++i)
		{
			--it;
			cout << *it << " ";
		}
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
	{
		persistent_set<int, my_linked_ptr> p;
		p.insert(1);
		p.insert(3);
		p.insert(2);
		p.insert(4);
		persistent_set<int, my_linked_ptr>::iterator it;
		it = p.end();
		for (int i = 0; i < 4; ++i)
		{
			--it;
			cout << *it << " ";
		}
		cout << "\n";
		++it;
		++it;
		cout << *it << endl;
		p.erase(it);
		it = p.end();
		for (int i = 0; i < 3; ++i)
		{
			--it;
			cout << *it << " ";
		}
		cout << "\n";
		persistent_set<int, my_linked_ptr> p2(p);
		p2.insert(3);
		it = p2.end();
		for (int i = 0; i < 4; ++i)
		{
			--it;
			cout << *it << " ";
		}
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
	return 0;
}