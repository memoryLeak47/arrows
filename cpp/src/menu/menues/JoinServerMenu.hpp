#ifndef __JOINSERVERMENU_CLASS__
#define __JOINSERVERMENU_CLASS__

#include "../Menu.hpp"

class EditField;

class JoinServerMenu : public Menu
{
	public:
		JoinServerMenu();
		void joinServer(); // called by the join-server-button
	private:
		EditField* ipField;
};

#include "../components/EditField.hpp"

#endif
