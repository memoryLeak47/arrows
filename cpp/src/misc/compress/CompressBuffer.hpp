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
		long cutLong();
		std::vector<std::vector<int>> cutMap();
		Compressable* cutByCompressID(CompressID);
		template <class T> T* cutCompressable();
		std::vector<void*> cutVectorByCompressID(CompressID);
		std::string cut(int amount); // removes <amount> chars from <chars> and returns the removed part
	private:
		int counter;
		std::string string;
};

#include <misc/Global.hpp>

template <class T>
T* CompressBuffer::cutCompressable()
{
	CompressID cid = (CompressID) cutChar();
	T* c = dynamic_cast<T*>(cutByCompressID(cid));
	if (c == nullptr)
	{
		Debug::error("cutCompressable() failed, CompressID=" + Converter::intToString(cid));
	}
	return c;
}

#endif
