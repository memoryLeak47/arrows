#ifndef __MENUCOMPONENT_CLASS__
#define __MENUCOMPONENT_CLASS__

#include "../math/pixel/PixelRect.hpp"

class ComponentContainer;
class PixelPosition;

class MenuComponent
{
	public:
		MenuComponent(ComponentContainer* parent, const PixelRect& rect);
		virtual ~MenuComponent();
		virtual void tick();
		virtual void render() const = 0;
		virtual void onClick(int mouseButton);
		virtual void onMouseEnter(const PixelVector&);
		virtual void onMouseMove(const PixelVector&);
		virtual void onMouseExit(const PixelVector&);
		virtual void onTextEntered(char key);
		virtual MenuComponent* getHoveredComponentRecursively() const; // overwritten by panels etcs..
		virtual PixelRect getAbsoluteRect() const;
		virtual PixelRect getRelativeRect() const;
		bool isEnabled() const;
		void setEnabled(bool);
	protected:
		void setRelativeRect(const PixelRect&);
		ComponentContainer* getParent() const;
	private:
		PixelRect rect; // relative rect
		ComponentContainer* parent;
		bool enabled;
};

#include "ComponentContainer.hpp"
#include "../math/pixel/PixelVector.hpp"

#endif
