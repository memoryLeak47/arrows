#include "ArrowShotSkill.hpp"

#include <misc/Debug.hpp>

ArrowShotSkill::ArrowShotSkill(Mob* owner_arg, const LobbySkill* lobbySkill)
	: TriggerSkill(owner_arg, lobbySkill)
{}

void ArrowShotSkill::onTrigger()
{
	Debug::screen("ARROWWWW");
}
