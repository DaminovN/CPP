#include<bits/stdc++.h>
#include "myVec.h"
using namespace std;


myVec::myVec() : small(0), isSmall(false), isEmpty(true) {}


myVec::myVec(const myVec& rhs) : isSmall(rhs.isSmall), isEmpty(rhs.isEmpty)
{
	if (rhs.isEmpty)
		return;
	if (rhs.isSmall)
	{
		small = rhs.small;
	}
	else 
	{
		big = rhs.big;
		big->count++;
	}
}

void myVec::separate()
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

int& myVec::operator[](int pos)
{
	if (isSmall && pos > 0)
		throw "out of bound";
	if (isSmall)
		return small;
	separate();
	return big->data[pos];
}

const int& myVec::operator[](int pos) const
{
	if (isSmall && pos > 0)
		throw "out of bound";
	if (isSmall)
		return small;
	return big->data[pos];
}

size_t myVec::size() const
{
	if (isEmpty)
		return (size_t) 0;
	if (isSmall)
        return (size_t) 1;
	return big->data.size();
}


void myVec::push_back(int rhs)
{
	if (isEmpty)
	{
		small = rhs;
		isSmall = true;
		isEmpty = false;
	}
	else 
	{
		if (isSmall)
		{
			int temp = small;
            sharedVec* newVec = new sharedVec();
            newVec->count = 1;
            newVec->data.push_back(temp);
            newVec->data.push_back(rhs);
            swap(newVec, big);
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
void myVec::normalize()
{
	if (!isEmpty && !isSmall && big->data.size() == 1)
	{
		separate();
		int temp = big->data[0];
		safe_delete();
		small = temp;
		isSmall = true;
	}
}

void myVec::pop_back()
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

bool myVec::empty() const
{
	return (size() == 0);
}


int& myVec::back()
{
	if (isEmpty)
		throw "out of bound";
	if (isSmall)
		return small;
	return operator[](big->data.size() - 1);
}
const int& myVec::back() const
{
	if (isEmpty)
		throw "out of bound";
	if (isSmall)
		return small;
	return operator[](big->data.size() - 1);
}

size_t myVec::begin() const
{
	return size_t(0);
}
size_t myVec::end() const
{
	return size();
}
void myVec::reverseAll()
{
	if (isEmpty || isSmall)
		return;
	separate();
	reverse(big->data.begin(), big->data.end());
}

void myVec::clear()
{
    if (!isSmall && !isEmpty)
	{
		separate();
		big->data.clear();
	}
    isEmpty = true;
}

void myVec::resize(size_t sz, int val)
{
	while(sz > size())
	{
		push_back(val);
	}
	while(sz < size())
	{
		pop_back();
	}
}
void myVec::resize(size_t sz)
{
	resize(sz, 0);
}

myVec::myVec(size_t sz) : myVec() 
{
	resize(sz);
}
myVec::myVec(size_t sz, int val) : myVec() 
{
	resize(sz, val);
}

void myVec::myFill(int val)
{
	if (isEmpty)
		return;
	if (isSmall)
		small = val;
	else 
	{
		separate();
		fill(big->data.begin(), big->data.end(), val);
	}
}
myVec& myVec::operator=(const myVec& rhs)
{
    isSmall = rhs.isSmall;
    isEmpty = rhs.isEmpty;
    if (rhs.isEmpty)
        return *this;
    if (rhs.isSmall)
    {
        small = rhs.small;
    }
    else
    {
        big = rhs.big;
        big->count++;
    }
    return *this;
}

/*main()
{
	myVec v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(i);
	}
	cout << v.size() << endl;
	myVec v2(v);
	cout << v2.size() << endl;
	v2[0] = 1;
	cout << v2.size() << endl;
	cout << v.size() << endl;
	return 0;
}*/
