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
	bimap<int, int>::left_iterator i = m.insert(2, 20);
	m.insert(1, 30);
	m.insert(3, 10);
	cout << (2 == *i) << endl;
	cout << (20 == *(i.flip())) << endl;
	cout << (std::prev(i).flip() == std::next(i.flip())) << endl;
	return 0;
}
