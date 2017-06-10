#ifndef MY_VEC
#define MY_VEC

#include<bits/stdc++.h>


struct sharedVec {
	std::vector<int> data;
	int count;
};

struct myVec {
public:
	myVec();
	myVec(size_t sz);
	myVec(size_t sz, int val);
    myVec(const myVec& rhs);
	~myVec();
	size_t size() const;
	void push_back(int rhs);
	void pop_back();
	int& operator[](int pos);
	const int& operator[](int pos) const;
    myVec& operator=(const myVec& rhs);
	bool empty() const;
	int& back();
	const int& back() const;
	size_t begin() const;
	size_t end() const;
	void reverseAll();
	void clear();
	void resize(size_t sz);
	void resize(size_t sz, int val);
	void myFill(int val);

private:
	void normalize();
	void safe_delete();
	void separate();

	union {
		int small;
		sharedVec* big;
	};

	bool isSmall;
	bool isEmpty;
};
#endif
