#ifndef __IDLER_CLASS__
#define __IDLER_CLASS__

#include "Entity.hpp"
#include <misc/compress/Compressable.hpp>

class Idler : public Entity, public Compressable
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
