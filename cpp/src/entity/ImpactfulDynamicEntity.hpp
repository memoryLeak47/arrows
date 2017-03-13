#ifndef __IMPACTFULDYNAMICENTITY_CLASS__
#define __IMPACTFULDYNAMICENTITY_CLASS__

class CompressBuffer;

#include "DynamicEntity.hpp"
#include <misc/compress/Compressable.hpp>

$$abstract$$
class ImpactfulDynamicEntity : public DynamicEntity, public Compressable
{
	public:
		ImpactfulDynamicEntity(const EntityGivethrough&);
		ImpactfulDynamicEntity(CompressBuffer*);
		virtual ~ImpactfulDynamicEntity() {}

		virtual std::string getCompressString() const override;
};
$!abstract$$

#endif
