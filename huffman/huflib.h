#ifndef HUFLIB
#define HUFLIB


#include<bits/stdc++.h>
struct huffman
{
public:
	huffman();
	void addInfo(uint8_t* & a, int sz);
	void buildTree();
	void buildTree(std::vector<std::pair<uint8_t, int>> res);
	std::pair<int, std::vector<uint8_t>> encode(uint8_t* & a, int sz);
	std::vector<std::pair<uint8_t, int>> getTreeCode();
	std::vector<uint8_t> decode(uint8_t* & a, int sz, int unNeededBits);
private:
	static const int alphabetSize = 256;
	unsigned long long int number[alphabetSize * 2];
	bool hufTreeBuilt = false;
	bool isRight[alphabetSize * 2];
	int leftSon[alphabetSize * 2], rightSon[alphabetSize * 2];
	int maxNode = alphabetSize;
	int tPar[alphabetSize * 2];
};

#endif