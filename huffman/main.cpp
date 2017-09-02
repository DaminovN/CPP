#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<fstream>
#include "huflib.h"
using namespace std;
//-----------------------------------------------------------------------
// FORMAT OF INPUT :
// argv[1] = "enc" or "dec"
// argv[2] = direction from where to read
// argv[3] = direction of file where to write output
//-------------------------------------------------------------------
int main(int argc, char ** argv)
{
	try {

	const int blockSize = 128000;
	if (argc != 4)
	{
		throw runtime_error("4 ARGUMENTS EXPECTED");
	}
	ifstream read;
	ofstream write;
	string s = argv[1];
	vector<pair<uint8_t, int>> tree;
	if (s == "enc")
	{
		write.open(argv[3]);
		read.open(argv[2]);
		weights hufT;
		if (read.fail() || write.fail())
		{
			throw runtime_error("SUCH FILE NOT FOUND");
		}
		// uint8_t* data;
		// data = new uint8_t[blockSize];
		unique_ptr<uint8_t[]> data(new uint8_t[blockSize]);
		while (!read.eof())
		{
			read.read((char *) (data.get()), blockSize);
			hufT.addInfo(data.get(), read.gcount());
		}
		tree = hufT.getTreeCode();
		uint32_t trSize = (uint32_t)tree.size();
		write.write((char *) &trSize, sizeof(int32_t));
		for (int i = 0; i < tree.size(); ++i)
		{
			write.write((char *) &tree[i].first, 1);
			write.write((char *) &tree[i].second, sizeof(int32_t));
		}
		read.clear();
		read.seekg(0);
		huffman encode(hufT);
		while (!read.eof())
		{
			read.read((char *) (data.get()), blockSize);
			pair<int, vector<uint8_t>> enc = encode.encode(data.get(), (int) read.gcount());
			uint32_t sz = enc.first;
			write.write((char *) &(sz), sizeof(int32_t));
			write.write((char *) enc.second.data(), enc.second.size());
		}
	}
	else if (s == "dec")
	{
		write.open(argv[3]);
		read.open(argv[2]);
		if (read.fail() || write.fail())
		{
			throw runtime_error("SUCH FILE NOT FOUND");
		}
		uint32_t trSize = 0;
		read.read((char *) &trSize, sizeof(int32_t));
		if (!read || trSize > alphabetSize)
			throw runtime_error("FILE IS DAMAGED");
		for (size_t i = 0; i < trSize; ++i)
		{
			tree.push_back({0 , 0});
			read.read((char *) &(tree[i].first), 1);
			if (!read)
				throw runtime_error("FILE IS DAMAGED");
			read.read((char *) &(tree[i].second), sizeof(int32_t));
			if (!read)
				throw runtime_error("FILE IS DAMAGED");
		}
		weights hufT(tree);
		huffman decode(hufT);
		unique_ptr<uint8_t[]> data(new uint8_t[blockSize]);
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
			read.read((char *) (data.get()), vecSize);
			vector<uint8_t> res = decode.decode(data.get(), vecSize, unNeed);
			write.write((char *) res.data(), res.size());
		}
	}
	else 
	{
		throw runtime_error("Undefined Operation");
	}
	}catch(runtime_error const& e) {
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}