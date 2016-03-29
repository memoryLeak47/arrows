#ifndef __SKILL_CLASS__
#define __SKILL_CLASS__

#include "../PlayerProperty.hpp"

class Skill : public PlayerProperty
{
	public:
		virtual ~Skill() {}
		static void init();
		static void uninit();
		static Skill* get(int);
		static int getAmount();
		static const std::vector<Skill*> getAllSkillsByAvatarID(char);
		virtual char getAvatarID() const = 0;

		// in the lobby-menu every sub-Skill e.g. ArrowShotSkill is exactly the same;
		// but in the game every sub-Skill has to be handled different (e.g. because of different charges)
		// for getting this: 
		// when the game starts every skill of the player has to be set to a clone of the original sub-Skill in Skill::skills
		virtual Skill* clone() const = 0;
	private:
		static std::vector<Skill*> skills;
		/*
			float charge;
			ServerGamePlayer? owner;
		*/
};

#endif
