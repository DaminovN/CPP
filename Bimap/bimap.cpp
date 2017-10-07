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
	m.insert(3, 6);
	m.insert(2, 8);
	m.insert(4, 4);
	m.insert(7, 3);
	m.insert(6, 7);
	m.insert(8, 9);

	expect_eq(5 ,5);
	expect_eq(3, 6);
	expect_eq(2, 8);
	expect_eq(4, 4);
	expect_eq(7, 3);
	expect_eq(6, 7);
	expect_eq(8, 9);
	return 0;
}
