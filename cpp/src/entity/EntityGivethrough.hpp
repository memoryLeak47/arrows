#ifndef __ENTITYGIVETHROUGH_CLASS__
#define __ENTITYGIVETHROUGH_CLASS__

#include <misc/compress/Compressable.hpp>
#include <math/game/GameVector.hpp>

class EntityGivethrough : public Compressable
{
	public:
		EntityGivethrough(const GameVector& position_arg, const GameVector& size_arg, const GameVector& speed_arg=GameVector(0.f,0.f), float rotation_arg=0, float spin_arg=0);
		EntityGivethrough(CompressBuffer*);

		virtual CompressID getCompressID() const override;
		virtual std::string getCompressString() const override;

		GameVector position, size, speed;
		float rotation, spin;
};

#endif
