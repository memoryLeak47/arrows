/*
 * PlayerPanel ist 60x60 Pixel groß.
 * AvatarIcon ist 45x45 Pixel groß.
 * {Item,Skill}Icons sind 15x15 Pixel groß.
 * 0; 15; 30; 45; 60
*/

package menu.components;

import java.awt.Color;

import core.Screen;
import menu.ComponentContainer;
import menu.components.icons.choosable.*;
import misc.Debug;
import misc.math.pixel.PixelRect;
import player.LobbyPlayer;

public class PlayerPanel extends ComponentContainer
{
	public static final int SKILL_ICON_SIZE = 15, ITEM_ICON_SIZE = 15, AVATAR_ICON_SIZE = 45;

	private LobbyPlayer player;

	public PlayerPanel(ComponentContainer parent, PixelRect rect, LobbyPlayer player)
	{
		super(parent, rect);
		this.player = player;

		// AvatarIcon
		getComponents().add(new AvatarIcon(this, new PixelRect(0,0,AVATAR_ICON_SIZE,AVATAR_ICON_SIZE), this.player));

		// SkillIcons
		getComponents().add(new SkillIcon(this, new PixelRect(0 ,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player, 0));
		getComponents().add(new SkillIcon(this, new PixelRect(15,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player, 1));
		getComponents().add(new SkillIcon(this, new PixelRect(30,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player, 2));
		getComponents().add(new SkillIcon(this, new PixelRect(45,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player, 3));

		// ItemIcons
		getComponents().add(new ItemIcon(this, new PixelRect(45,0 ,ITEM_ICON_SIZE,ITEM_ICON_SIZE), this.player, 0));
		getComponents().add(new ItemIcon(this, new PixelRect(45,15,ITEM_ICON_SIZE,ITEM_ICON_SIZE), this.player, 1));
		getComponents().add(new ItemIcon(this, new PixelRect(45,30,ITEM_ICON_SIZE,ITEM_ICON_SIZE), this.player, 2));
	}

	@Override public void render()
	{
		super.render(); // zeichne alle MenuComponents
		if (player != null && player.isLocked())
		{
			Screen.g().setColor(Color.YELLOW);
			Screen.g().drawRect(getOffset().getX()-2, getOffset().getY()-2, getWidth()+4, getHeight()+4);
		}
		Screen.g().setColor(Color.WHITE);
		Screen.g().drawString(player.getName(), getOffset().getX(), getOffset().getY() + 72);
		Screen.g().drawString(player.getRank() +"", getOffset().getX(), getOffset().getY() + 10);
	}

	public LobbyPlayer getPlayer() { return player; }
}
