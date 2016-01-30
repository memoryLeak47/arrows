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
		void* cutByCID(CID);
	private:
		void cut(int amount); // removes <amount> chars from <chars>
		std::string string;
};

#include "Compressable.h"

#endif
