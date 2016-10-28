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
		template <class T = Compressable> T* cutCompressable();
		std::vector<void*> cutVectorByCompressID(CompressID);
		std::string cut(int amount); // removes <amount> chars from <chars> and returns the removed part
	private:
		int counter;
		std::string string;
};

#include <misc/Debug.hpp>

template <class T = Compressable>
T* CompressBuffer::cutCompressable()
{
	T* c = dynamic_cast<T*>(cutByCompressID((CompressID) cutChar()));
	if (c == nullptr)
	{
		Debug::error("cutCompressable() failed");
		return nullptr;
	}
	else
	{
		return c;
	}
}

#endif
