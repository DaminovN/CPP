#include <bits/stdc++.h>
#include "bimap.h"

using namespace std;

bimap<int, int> m;
void expect_eq(int a, int b)
{
	auto i = m.find_left(a);
	cout << !(i == m.end_left()) << endl;
	cout << (*i == a) << endl;
	cout << (*(i.flip()) == b) << endl;
	auto j = m.find_right(b);
	cout << !(j == m.end_right()) << endl;
	cout << (*j == b) << endl;
	cout << (*(j.flip()) == a) << endl;
}

int main()
{
	m.insert(5 ,5);
	m.insert(3, 4);
	m.insert(5, 6);
	expect_eq(1, 2);
	expect_eq(3, 4);
	expect_eq(5, 6);
	cout << (m.find_left(2) == m.end_left()) << endl;
	cout << (m.find_left(4) == m.end_left()) << endl;

	cout << (m.find_right(1) == m.end_right()) << endl;
	cout << (m.find_right(3) == m.end_right()) << endl;
	cout << (m.find_right(5) == m.end_right()) << endl;
	return 0;
}
