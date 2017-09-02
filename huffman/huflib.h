#ifndef HUFLIB
#define HUFLIB


#include<iostream>
#include<string>
#include<memory>
#include<vector>
const size_t alphabetSize = 256;
struct weights
{
	weights();
	weights(std::vector<std::pair<uint8_t, int>> const& res);
	void addInfo(const uint8_t* a, size_t sz);
	std::vector<std::pair<uint8_t, int>> getTreeCode() const;
	unsigned long long int number[alphabetSize] = {};
};
struct huffman
{
public:
	huffman(weights const&);
	// huffman(std::vector<std::pair<uint8_t, int>> res);
	// void buildTree();
	// void buildTree(std::vector<std::pair<uint8_t, int>> res);
	std::pair<int, std::vector<uint8_t>> encode(const uint8_t* a, size_t sz) const;
	std::vector<uint8_t> decode(const uint8_t* a, size_t sz, int unNeededBits) const;
private:
	bool isRight[alphabetSize * 2] = {};
	int leftSon[alphabetSize * 2] = {}, rightSon[alphabetSize * 2] = {};
	int maxNode = alphabetSize - 1;
	int tPar[alphabetSize * 2] = {};
};

#endif