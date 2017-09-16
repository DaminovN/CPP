#include <bits/stdc++.h>
#include "bimap.h"

using namespace std;



int main()
{
	bimap<int, int> m;
	m.insert(1, 5);
	m.insert(1, 5);
	// printTree((m.data)->root);
	bimap<int, int>::left_iterator it = m.begin_left();
	next(it);

	return 0;
}