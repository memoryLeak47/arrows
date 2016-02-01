#ifndef __COMPRESSBUFFER_CLASS__
#define __COMPRESSBUFFER_CLASS__

#include <string>

typedef char CID;

class CompressBuffer
{
	public:
		CompressBuffer(const std::string&);
		int cutInt();
		char cutChar();
		bool cutBool();
		void* cutByCID(CID);
	private:
		std::string cut(int amount); // removes <amount> chars from <chars> and returns the removed part
		std::string string;
};

#include "Compressable.hpp"

#endif
