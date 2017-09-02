#include<iostream>
#include<cstring>
#include<memory>
#include<vector>
#include<algorithm>
#include<cstdio>
#include "huflib.h"
using namespace std;
hTree::hTree() {}

void hTree::addInfo(uint8_t* & a, size_t sz)
{
	hufTreeBuilt = false;
	for (size_t i = 0; i < sz; ++i)
	{
		// cerr << a[i] << " ";
		++number[a[i]];
	}
}
void hTree::buildTree()
{
	// cerr << "BUILDING :)\n";
	hufTreeBuilt = true;
	int first[alphabetSize] = {0};
	for (int i = 0; i < alphabetSize; ++i)
		first[i] = i;
	sort(first, first + alphabetSize, [this](int a, int b) { return number[a] < number[b]; });
	int second[alphabetSize] = {0};
	int sz2 = 0;
	int fPointer = 0, sPointer = 0;
	int a, b;
	while (alphabetSize - fPointer + sz2 - sPointer != 1)
	{
		if (fPointer < alphabetSize && number[first[fPointer]] == 0)
		{
			++fPointer;
			continue;
		}
		if (sPointer >= sz2 || (fPointer < alphabetSize && number[first[fPointer]] < number[second[sPointer]]))
		{
			a = first[fPointer];
			fPointer++;
		}
		else 
		{
			a = second[sPointer];
			sPointer++;
		}
		if (sPointer >= sz2 || (fPointer < alphabetSize && number[first[fPointer]] < number[second[sPointer]]))
		{
			b = first[fPointer];
			fPointer++;
		}
		else 
		{
			b = second[sPointer];
			sPointer++;
		}
		second[sz2++] = ++maxNode;
		number[maxNode] = number[a] + number[b];
		tPar[a] = tPar[b] = maxNode;
		leftSon[maxNode] = a;
		rightSon[maxNode] = b;
		isRight[b] = true;
	}
}
void hTree::buildTree(vector<pair<uint8_t, int>> res)
{
	for (size_t i = 0; i < res.size(); ++i)
	{
		number[res[i].first] = res[i].second;
	}
	buildTree();
}
vector<pair<uint8_t, int>> hTree::getTreeCode()
{
	vector<pair<uint8_t, int>> res;
	for (int i = 0; i < alphabetSize; ++i)
	{
		if (number[i])
		{
			res.push_back({(uint8_t) i, number[i]});
		}
	}
	return res;

}


huffman::huffman(hTree& newTree) : theTree(newTree)
{
	// cerr << "BUILT " << theTree.hufTreeBuilt << endl;
	if (!theTree.hufTreeBuilt)
		theTree.buildTree();
	// cerr << "FINISHED\n";
}


pair<int, vector<uint8_t>> huffman::encode(uint8_t* & a, int sz)
{
	// if (!hufTreeBuilt)
	// 	buildTree();
	vector<uint8_t> v;
	int cnt = 0;
	uint8_t val = 0;
	for (int i = 0; i < sz; ++i)
	{
		// cerr << a[i] << " " << i << endl;
		int pos = a[i];
		while (pos != theTree.maxNode)
		{
			val <<= 1;
			val += (int) theTree.isRight[pos];
			++cnt;
			if (cnt == 8)
			{
				v.push_back(val);
				val = cnt = 0;
			}
			pos = theTree.tPar[pos];
		}
	}
	int sz2 = v.size() * 8 + cnt;
	if (cnt != 0)
	{
		val <<= (8 - cnt);
		v.push_back(val);
	}
	// cerr << "THE SIZE IS " << v.size() << " " << sz2 << " " << (int) v[0] << endl;
	return {sz2, v};
}
vector<uint8_t> huffman::decode(uint8_t* & a, int sz, int unNeededBits)
{
	vector<uint8_t> res;
	a[sz - 1] >>= unNeededBits;
	// cerr << "IN DECODE " << (int) a[sz - 1] << endl;
	vector<bool> bl;
	int curSz;
	for (int i = 0; i < sz - 1; ++i)
	{
		curSz = bl.size();
		for (int j = 0; j < 8; ++j)
		{
			bl.push_back(a[i] % 2);
			a[i] >>= 1;
		}
		reverse(bl.begin() + curSz, bl.end());
	}
	if (sz != 0)
	{
		curSz = bl.size();
		for (int j = 0; j < 8 - unNeededBits; ++j)
		{
			bl.push_back(a[sz - 1] % 2);
			a[sz - 1] >>= 1;
		}
		reverse(bl.begin() + curSz, bl.end());
	}
	int curPos = theTree.maxNode;
	for (int i = bl.size() - 1; i >= 0; --i)
	{
		curPos = (bl[i] == 0) ? theTree.leftSon[curPos] : theTree.rightSon[curPos];
		if (curPos < 256)
		{
			// cerr << "FOUND " << (char) curPos << endl;
			res.push_back(curPos);
			curPos = theTree.maxNode;
		}
	}
	reverse(res.begin(), res.end());
	// cerr << "DECODE " << res.size() << " " << (int) res[0] << endl;
	return res;
}
/*int main()
{
	
}*/