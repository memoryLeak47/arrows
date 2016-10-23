#ifndef __COMPRESSBUFFER_CLASS__
#define __COMPRESSBUFFER_CLASS__

class Compressable;

#include <string>
#include <vector>
#include "CompressID.hpp"

class CompressBuffer
{
	public:
		CompressBuffer(const std::string&);
		std::string cutString();
		int cutInt();
		float cutFloat();
		char cutChar();
		short cutShort();
		bool cutBool();
		std::vector<std::vector<int>> cutMap();
		Compressable* cutByCompressID(CompressID);
		Compressable* cutCompressable();
		std::vector<void*> cutVectorByCompressID(CompressID);
		std::string cut(int amount); // removes <amount> chars from <chars> and returns the removed part
	private:
		int counter;
		std::string string;
};

#endif
