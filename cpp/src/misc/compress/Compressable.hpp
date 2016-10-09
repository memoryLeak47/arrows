#ifndef __COMPRESSABLE_CLASS__
#define __COMPRESSABLE_CLASS__

#include <misc/Global.hpp>

#include "Cid.hpp"

#include <string>
#include <vector>

class Compressable // represents Compressable.java and Compressor.java
{
	public:
		virtual ~Compressable() {}
		virtual std::string getCompressString() const = 0; // conversion to chars
		virtual CID getCID() const = 0;
		std::string compress() const; // CID + conversion to chars
		static void* decompress(const std::string&); // creates CompressBuffer -> gets object
	protected:
		static std::string compressVector(const std::vector<Compressable*>&);
		static std::string compressBool(bool);
		static std::string compressInt(int);
		static std::string compressFloat(float);
		static std::string compressShort(short);
		static std::string compressString(const std::string&);
		static std::string compressMap(const std::vector<std::vector<int>>& map);
};

#endif
