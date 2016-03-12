#include "Compressable.hpp"

#include "CompressBuffer.hpp"

std::string Compressable::compress() const
{
	return getCID() + toString();
}

void* Compressable::decompress(const std::string& string)
{
	CompressBuffer buffer(string);
	void* object = buffer.cutByCID(buffer.cutChar());
	return object;
}

std::string Compressable::compressBool(bool b)
{
	return b? "1" : "0";
}

std::string Compressable::compressInt(int i)
{
	std::string s;
	s += (i >> 24);
	s += ((i << 8) >> 24);
	s += ((i << 16) >> 24);
	s += ((i << 24) >> 24);
	return s;
}

std::string Compressable::compressString(const std::string& s)
{
	return compressInt(s.length()) + s;
}
