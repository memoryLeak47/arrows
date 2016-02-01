#include "CompressBuffer.hpp"

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
	std::string tmp = cut(1);
	return tmp[0];
}

bool CompressBuffer::cutBool()
{
	std::string tmp = cut(1);
	return tmp[0] == '1';
}

void* CompressBuffer::cutByCID(CID cid)
{
	return (char*)0;
}

std::string CompressBuffer::cut(int amount)
{
	std::string ret = string.substr(0, amount);
	string = string.substr(amount, string.size());
	return ret;
}
