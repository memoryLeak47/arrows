#include "CompressBuffer.h"

CompressBuffer::CompressBuffer(const std::string& s)
{
	this->string = s;
}

int CompressBuffer::cutInt()
{
	return 2;
}

char CompressBuffer::cutChar()
{
	return 's';
}

void* CompressBuffer::cutByCID(CID cid)
{
	return (char*)0;
}

void CompressBuffer::cut(int amount)
{
	string = string.substr(amount, string.size());
}
