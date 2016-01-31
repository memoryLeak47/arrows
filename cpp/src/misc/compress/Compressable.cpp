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
