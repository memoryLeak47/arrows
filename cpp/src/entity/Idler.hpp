#ifndef __IDLER_CLASS__
#define __IDLER_CLASS__

class Body;
class CompressBuffer;

#include "ImpactfulDynamicEntity.hpp"
#include <string>

class Idler : public ImpactfulDynamicEntity
{
	public:
		Idler(Body*);
		Idler(CompressBuffer*);
		virtual ~Idler() {}

		// compress
		std::string getCompressString() const override;
		virtual EntityType getEntityType() const override;
};

#endif
