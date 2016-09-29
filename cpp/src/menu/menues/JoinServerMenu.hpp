#ifndef __JOINSERVERMENU_CLASS__
#define __JOINSERVERMENU_CLASS__

#include <menu/Menu.hpp>

class EditField;

class JoinServerMenu : public Menu
{
	public:
		JoinServerMenu();
		void joinServer(); // called by the join-server-button
	private:
		EditField* ipField;
};

#include <menu/components/EditField.hpp>

#endif
