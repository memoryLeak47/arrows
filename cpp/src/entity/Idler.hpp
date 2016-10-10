#ifndef __IDLER_CLASS__
#define __IDLER_CLASS__

#include "ImpactfulDynamicEntity.hpp"

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
