#ifndef HUFLIB
#define HUFLIB


#include<bits/stdc++.h>
void addInfo(uint8_t* & a, int sz);
void buildTree();
void buildTree(std::vector<std::pair<uint8_t, int>> res);
bool hufCmp(int a, int b);
std::pair<int, std::vector<uint8_t>> encode(uint8_t* & a, int sz);
std::vector<std::pair<uint8_t, int>> getTreeCode();
std::vector<uint8_t> decode(uint8_t* & a, int sz, int unNeededBits);

#endif