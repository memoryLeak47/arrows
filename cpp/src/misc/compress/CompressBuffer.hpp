#ifndef __COMPRESSBUFFER_CLASS__
#define __COMPRESSBUFFER_CLASS__

#include <string>
#include <vector>

#include <misc/Global.hpp>
#include "cid.hpp"

class CompressBuffer
{
	public:
		CompressBuffer(const std::string&);
		std::string cutString();
		int cutInt();
		char cutChar();
		short cutShort();
		bool cutBool();
		std::vector<std::vector<int>> cutMap();
		void* cutByCID(CID);
		std::vector<void*> cutVectorByCID(CID);
		std::string cut(int amount); // removes <amount> chars from <chars> and returns the removed part
	private:
		int counter;
		std::string string;
};

#include "Compressable.hpp"

#endif
