#ifndef __POPUPMENU_CLASS__
#define __POPUPMENU_CLASS__

#include <string>

#include "../Menu.hpp"

class PopupMenu : public Menu
{
	public:
		PopupMenu(const std::string&);
	private:
		std::string text;
};

#endif
