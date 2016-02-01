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
	return "__COMPRESS_INT_TODO__"; // TODO
}
