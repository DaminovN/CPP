#include <bits/stdc++.h>
#include "bimap.h"

using namespace std;



int main()
{
	bimap<int, int> m;
	m.insert(1, 2);
	auto i = m.find_left(1);
	cout << (i == m.end_left()) << endl;
	cout << *i << endl;
	cout << (*i == 1) << endl;
	cout << (*(i.flip()) == 2) << endl;
	return 0;
}
