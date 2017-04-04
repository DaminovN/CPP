#include<bits/stdc++.h>
#include "big_integer.h"

using namespace std;

big_integer::big_integer()
{
	v.resize(1, 0);
	sign = 1;
}
big_integer::big_integer(big_integer const& value)
{
	v.resize(value.v.size());
	for (int i = 0; i < value.v.size(); ++i )
	{
		v[i] = value.v[i];
	}
	sign = value.sign;
}
big_integer::big_integer(int value)
{
	if (value >= 0)
		sign = 1;
	else
		sign = -1;
	value = abs(value);
	v.clear();
	if (value == 0)
		v.push_back(0);
	while (value > 0)
	{
		v.push_back(value%10);
		value /= 10;
	}
}
big_integer::big_integer(string const& value)
{
	v.clear();
	sign = 1;
	int end = 0;
	if (value[0] == '-')
		sign = -1, end = 1;
	for (int i = value.length() - 1; i >= end; --i)
	{
		v.push_back((int)(value[i] - '0'));
	}
}
big_integer::~big_integer() {}
void print(big_integer const& value)
{
	if (value.sign == -1)
		printf("-");
	for (int i = value.v.size() - 1; i >= 0; --i)
	{
		printf("%d", value.v[i]);
	}
	printf("\n");
}
int main()
{
	string s = "123";
	big_integer number(s);
	print(number);
	return 0;
}