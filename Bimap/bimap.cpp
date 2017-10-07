#include <bits/stdc++.h>
#include "bimap.h"

using namespace std;



int main()
{
	bimap<int, string> m;
	m.insert(1, "kek");
	cout << *(m.begin_left().flip()) << endl;
	return 0;
}
