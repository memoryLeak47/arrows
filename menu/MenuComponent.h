#ifndef __MENUCOMPONENT_CLASS__
#define __MENUCOMPONENT_CLASS__

class MenuComponent
{
	public:
		virtual void tick();
		virtual void render() = 0;
};

#endif
