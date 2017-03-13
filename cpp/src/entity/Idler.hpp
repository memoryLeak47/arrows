#ifndef __IDLER_CLASS__
#define __IDLER_CLASS__

class CompressBuffer;

#include "ImpactfulDynamicEntity.hpp"
#include <string>

$$abstract$$
class Idler : public ImpactfulDynamicEntity
{
	public:
		Idler(const EntityGivethrough&);
		Idler(CompressBuffer*);
		virtual ~Idler() {}

		// compress
		std::string getCompressString() const override;
		virtual EntityType getEntityType() const override;
};
$!abstract$$

#endif
