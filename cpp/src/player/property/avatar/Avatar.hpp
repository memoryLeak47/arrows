#ifndef __AVATAR_CLASS__
#define __AVATAR_CLASS__

#include "../PlayerProperty.hpp"

class Avatar : public PlayerProperty
{
	public:
		static void init();
		static void uninit();
		static Avatar* get(int);
		static int getAmount();
		static const std::vector<Avatar*> getAllAvatars();
		char getID() const override;
		virtual int getMassStat() const;
		virtual float getHealthStat() const;
	private:
		void setID(char);
		static std::vector<Avatar*> avatars;
		char id;
};

#endif
