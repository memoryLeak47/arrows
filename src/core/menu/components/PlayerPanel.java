/*
 * PlayerPanel ist 60x60 Pixel groß.
 * AvatarIcon ist 45x45 Pixel groß.
 * {Item,Skill}Icons sind 15x15 Pixel groß.
 * 0; 15; 30; 45; 60
*/

package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.ComponentContainer;
import core.menu.components.icons.AvatarIcon;
import core.menu.components.icons.SkillIcon;
import core.menu.components.icons.ItemIcon;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class PlayerPanel extends ComponentContainer
{
	private LobbyPlayer player; // player to display stats of

	public PlayerPanel(ComponentContainer parent, Rect rect, LobbyPlayer player)
	{
		super(parent, rect);
		this.player = player; // set player

		// AvatarIcon
		getComponents().add(new AvatarIcon(this, new Rect(0,0,45,45), this.player.getAvatarID()));
		// SkillIcons
		getComponents().add(new SkillIcon(this, new Rect(0,45,15,15), this.player.getSkillIDs()[0]));
		getComponents().add(new SkillIcon(this, new Rect(15,45,15,15), this.player.getSkillIDs()[1]));
		getComponents().add(new SkillIcon(this, new Rect(30,45,15,15), this.player.getSkillIDs()[2]));
		getComponents().add(new SkillIcon(this, new Rect(45,45,15,15), this.player.getSkillIDs()[3]));
		// ItemIcons
		getComponents().add(new ItemIcon(this, new Rect(45,0,15,15), this.player.getItemIDs()[0]));
		getComponents().add(new ItemIcon(this, new Rect(45,15,15,15), this.player.getItemIDs()[1]));
		getComponents().add(new ItemIcon(this, new Rect(45,30,15,15), this.player.getItemIDs()[2]));
	}

	@Override public void render()
	{
		if (player.isLocked())
		{
			Screen.g().setColor(Color.LIGHT_GRAY); // set color to yellow
		}
		else
		{
			Screen.g().setColor(Color.YELLOW); // set color to yellow
		}
		super.render();
	}
}
