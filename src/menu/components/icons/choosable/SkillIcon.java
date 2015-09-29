package menu.components.icons.choosable;

import core.Main;
import menu.components.icons.ChoosableIcon;
import menu.ComponentContainer;
import menu.menues.LobbyMenu;
import menu.menues.ChoosePlayerPropertyMenu;
import game.skill.Skill;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class SkillIcon extends ChoosableIcon
{
	private LobbyPlayer player;
	private int number;

	public SkillIcon(ComponentContainer parent, Rect rect, LobbyPlayer player, int number)
	{
		super(parent, rect);
		this.player = player;;
		this.number = number;
	}

	@Override public void onClick(int mouseButton)
	{
		if (isChoosable())
		{
			Main.getMenues().add(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu().getLocalPlayer().getSkillPacket(), Skill.getAllSkills()));
		}
	}

	// Getter
	@Override public int getChoosePhase() { return LobbyMenu.SKILL_PHASE; }
	@Override public ImageID getImageID()
	{
		if ((player.getSkillPacket() == null) 
				|| (player.getSkillPacket().getSkills()[number] == null) 
				|| (player.getSkillPacket().getSkills()[number].getIconImageID() == null))
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		return player.getSkillPacket().getSkills()[number].getIconImageID();
	}
	public Skill getSkill() { return player.getSkillPacket().getSkills()[number]; }
}
