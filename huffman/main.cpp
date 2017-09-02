#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<fstream>
#include "huflib.h"
using namespace std;
const int blockSize = 128000;
pair<int, vector<uint8_t>> enc;
vector<pair<uint8_t, int>> tree;
vector<uint8_t> res;
//-----------------------------------------------------------------------
// FORMAT OF INPUT :
// argv[1] = "enc" or "dec"
// argv[2] = direction from where to read
// argv[3] = direction of file where to write output
//-------------------------------------------------------------------
int main(int argc, char ** argv)
{
	if (argc != 4)
	{
		throw runtime_error("4 ARGUMENTS EXPECTED");
	}
	ifstream read;
	ofstream write;
	string s = argv[1];
	if (s == "enc")
	{
		write.open(argv[3]);
		read.open(argv[2]);
		huffman encode;
		if (read.fail())
		{
			write.close();
			throw runtime_error("SUCH FILE NOT FOUND");
		}
		uint8_t* data;
		data = new uint8_t[blockSize];
		while (!read.eof())
		{
			read.read((char *) data, blockSize);
			encode.addInfo(data, read.gcount());
		}
		tree = encode.getTreeCode();
		uint32_t trSize = (uint32_t)tree.size();
		write.write((char *) &trSize, sizeof(int32_t));
		for (int i = 0; i < tree.size(); ++i)
		{
			write.write((char *) &tree[i].first, 1);
			write.write((char *) &tree[i].second, sizeof(int32_t));
		}
		read.clear();
		read.seekg(0);
		while (!read.eof())
		{
			read.read((char *)data, blockSize);
			enc = encode.encode(data, (int) read.gcount());
			uint32_t sz = enc.first;
			write.write((char *) &(sz), sizeof(int32_t));
			write.write((char *) enc.second.data(), enc.second.size());
		}
		delete[] data;
		read.close();
		write.close();
	}
	else if (s == "dec")
	{
		write.open(argv[3]);
		read.open(argv[2]);
		huffman decode;
		if (read.fail())
		{
			write.close();
			throw runtime_error("SUCH FILE NOT FOUND");
		}
		uint32_t trSize = 0;
		read.read((char *) &trSize, sizeof(int32_t));
		for (size_t i = 0; i < trSize; ++i)
		{
			tree.push_back({0 , 0});
			read.read((char *) &(tree[i].first), 1);
			read.read((char *) &(tree[i].second), sizeof(int32_t));
		}
		decode.buildTree(tree);
		uint8_t* data;
		data = new uint8_t[blockSize];
		while(!read.eof())
		{
			uint32_t sz = 0;
			read.read((char *) &(sz), sizeof(int32_t));
			int vecSize = sz;
			int unNeed = 0;
			if (sz % 8 != 0)
			{
				unNeed = 8 - (sz % 8);
			}
			vecSize += unNeed;
			vecSize /= 8;
			read.read((char *) data, vecSize);
			res = decode.decode(data, vecSize, unNeed);
			write.write((char *) res.data(), res.size());
		}
		delete[] data;
		read.close();
		write.close();
	}
	else 
	{
		throw runtime_error("Undefined Operation");
	}
	return 0;
}