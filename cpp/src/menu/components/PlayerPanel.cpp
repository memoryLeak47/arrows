#include "PlayerPanel.hpp"

#include "../../core/Screen.hpp"
#include "AvatarIcon.hpp"
#include "SkillIcon.hpp"
#include "ItemIcon.hpp"

PlayerPanel::PlayerPanel(LobbyPlayer* p, LobbyMenu* m, TeamPanel* c, const PixelRect& r) : Panel(c, r), player(p), lobby(m)
{
	addComponent(new AvatarIcon(getPlayer(), getLobbyMenu(), this, PixelRect(0,0,AVATAR_ICON_SIZE,AVATAR_ICON_SIZE)));

	// SkillIcons
	addComponent(new SkillIcon(0, getPlayer(), getLobbyMenu(), this,  PixelRect(0 ,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));
	addComponent(new SkillIcon(1, getPlayer(), getLobbyMenu(), this,  PixelRect(15,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));
	addComponent(new SkillIcon(2, getPlayer(), getLobbyMenu(), this,  PixelRect(30,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));
	addComponent(new SkillIcon(3, getPlayer(), getLobbyMenu(), this,  PixelRect(45,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));

	// ItemIcons
	addComponent(new ItemIcon(0, getPlayer(), getLobbyMenu(), this, PixelRect(45,0 ,ITEM_ICON_SIZE,ITEM_ICON_SIZE)));
	addComponent(new ItemIcon(1, getPlayer(), getLobbyMenu(), this, PixelRect(45,15,ITEM_ICON_SIZE,ITEM_ICON_SIZE)));
	addComponent(new ItemIcon(2, getPlayer(), getLobbyMenu(), this, PixelRect(45,30,ITEM_ICON_SIZE,ITEM_ICON_SIZE)));
}

void PlayerPanel::render() const
{
	Panel::render();
	if (getPlayer() != NULL && getPlayer()->getLockUserPacket()->isLocked())
	{
		Screen::drawRect(PixelRect(getAbsoluteRect().getPosition().getX()-2, getAbsoluteRect().getPosition().getY()-2, getRelativeRect().getSize().getX()+4, getRelativeRect().getSize().getY()), sf::Color::Yellow);
	}
	Screen::drawText(getPlayer()->getLoginUserPacket()->getName(), PixelVector(getAbsoluteRect().getPosition().getX(), getAbsoluteRect().getPosition().getY() + 72), sf::Color::White);
	Screen::drawText("" + getPlayer()->getLoginUserPacket()->getRank(), PixelVector(getAbsoluteRect().getPosition().getX(), getAbsoluteRect().getPosition().getY() + 10), sf::Color::White);
}

LobbyPlayer* PlayerPanel::getPlayer() const
{
	return player;
}

LobbyMenu* PlayerPanel::getLobbyMenu() const
{
	return lobby;
}
