#ifndef __LOBBYSKILL_CLASS__
#define __LOBBYSKILL_CLASS__

#include <player/property/PlayerProperty.hpp>
#include <vector>

class Skill;

class LobbySkill : public PlayerProperty
{
	public:
		virtual ~LobbySkill() {}
		static void init();
		static void uninit();
		static LobbySkill* get(int);
		static int getAmount();
		static const std::vector<LobbySkill*> getAllLobbySkillsByAvatarID(char);
		virtual char getAvatarID() const = 0;

		// in the lobby-menu every sub-Skill e.g. LobbyArrowShotSkill is exactly the same;
		// but in the game every sub-Skill has to be handled different (e.g. because of different charges)
		// for getting this: 
		// when the game starts every skill of the player has to be set to a clone of the original sub-Skill in Skill::skills
		Skill* createGameSkill() const;
	private:
		static std::vector<LobbySkill*> skills;
		/*
			float charge;
			ServerGamePlayer? owner;
		*/
};

#endif
