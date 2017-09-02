#ifndef HUFLIB
#define HUFLIB


#include<iostream>
#include<string>
#include<memory>
#include<vector>
struct hTree
{
	hTree();
	std::vector<std::pair<uint8_t, int>> getTreeCode();
	void addInfo(uint8_t* & a, size_t sz);
	void buildTree();
	void buildTree(std::vector<std::pair<uint8_t, int>> res);
	static const int alphabetSize = 256;
	unsigned long long int number[alphabetSize * 2] = {};
	bool hufTreeBuilt = false;
	int maxNode = alphabetSize - 1;
	bool isRight[alphabetSize * 2] = {};
	int leftSon[alphabetSize * 2] = {}, rightSon[alphabetSize * 2] = {};
	int tPar[alphabetSize * 2] = {};
};
struct huffman
{
public:
	// huffman(std::vector<std::pair<uint8_t, int>> &res);
	huffman(hTree&);
	std::pair<int, std::vector<uint8_t>> encode(uint8_t* & a, int sz);
	std::vector<uint8_t> decode(uint8_t* & a, int sz, int unNeededBits);
private:
	hTree theTree;
	/*static const int alphabetSize = 256;
	unsigned long long int number[alphabetSize * 2] = {};
	bool hufTreeBuilt = false;
	bool isRight[alphabetSize * 2] = {};
	int leftSon[alphabetSize * 2] = {}, rightSon[alphabetSize * 2] = {};
	int maxNode = 0;
	int tPar[alphabetSize * 2] = {};*/
};

#endif