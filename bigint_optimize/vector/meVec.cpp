#include<bits/stdc++.h>
#include "myVec.h"
using namespace std;


myVec::myVec() : val.small(0), isSmall(false), isEmpty(true) {}

myVec::myVec(int rhs) : val.small(rhs), isSmall(true), isEmpty(false) {}

// myVec::myVec(myVec rhs) : val(rhs.val), isSmall(rhs.isSmall), isEmpty(rhs.isEmpty) {}

int myVec::operator[](int pos)
{
	if (isSmall && pos > 0)
		throw "out of bound";
	if (isSmall)
		return val.small;
	return big->data[pos];
}

size_t size()
{
	if (isEmpty)
		return (size_t) 0;
	if (isSmall)
		return (size_t) 1;
	return big->data.size();
}

void separate()
{
	if (big->count > 1)
	{
		sharedVec* newVec = new sharedVec();
		big->count--;
		newVec->data = big->data;
		newVec->count = 1;
		swap(newVec, big);
	}
}

void push_back(int rhs)
{
	if (isEmpty)
		myVec(rhs);
	else 
	{
		if (isSmall)
		{
			int temp = small;
			big->data.push_back(temp);
			big->data.push_back(rhs);
			isSmall = false;
		}
		else
		{
			separate();
			big->data.push_back(rhs);
		}
	}
}

void myVec::safe_delete()
{
	if (big->count > 1)
		big->count--;
	else 
		delete big;
}
myVec::~myVec()
{
	if (!isEmpty && !isSmall)
		safe_delete();
}
void normalize()
{
	if (!isEmpty && !isSmall && big->data.size() == 1)
	{
		separate();
		int temp = big->data[0];
		val.small = rhs;
		isSmall = true;
		safe_delete();
	}
}

void pop_back()
{
	if (isEmpty)
		throw "size empty";
	if (isSmall)
	{
		isSmall = false;
		isEmpty = true;
	}
	else 
	{
		separate();
		big->data.pop_back();
	}
	normalize();
}

main()
{
	return 0;
}