#ifndef HUFLIB
#define HUFLIB


#include<iostream>
#include<string>
#include<memory>
#include<vector>
struct weights
{
	weights();
	weights(std::vector<std::pair<uint8_t, int>> res);
	void addInfo(uint8_t* & a, int sz);
	std::vector<std::pair<uint8_t, int>> getTreeCode();
	unsigned long long int number[256 * 2] = {};
	static const int alphabetSize = 256;
};
struct huffman
{
public:
	huffman(weights);
	// huffman(std::vector<std::pair<uint8_t, int>> res);
	// void buildTree();
	// void buildTree(std::vector<std::pair<uint8_t, int>> res);
	std::pair<int, std::vector<uint8_t>> encode(uint8_t* & a, int sz);
	std::vector<uint8_t> decode(uint8_t* & a, int sz, int unNeededBits);
private:
	static const int alphabetSize = 256;
	bool hufTreeBuilt = false;
	bool isRight[alphabetSize * 2] = {};
	int leftSon[alphabetSize * 2] = {}, rightSon[alphabetSize * 2] = {};
	int maxNode = alphabetSize - 1;
	int tPar[alphabetSize * 2] = {};
};

#endif