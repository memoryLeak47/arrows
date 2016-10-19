#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

#include <misc/compress/Compressable.hpp>
#include "Actions.hpp"

class Mob;
class CompressBuffer;

class Controller : public Compressable
{
	public:
		Controller() {}
		Controller(CompressBuffer*);
		virtual ~Controller() {}

		// compress
		std::string getCompressString() const override;

		Actions getActions() const;
	private:
		void setActions(const Actions); // Setzt Actions auf das übergebene
		Actions actions;
	friend class GameInterface;
	friend class GamePlayer;
};

#include <game/GameInterface.hpp>
#include <player/GamePlayer.hpp>
#include <entity/Mob.hpp>
#include <misc/compress/CompressBuffer.hpp>

#endif
