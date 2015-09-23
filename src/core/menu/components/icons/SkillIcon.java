package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
import core.menu.menues.LobbyMenu;
import game.skill.Skill;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.Rect;

public class SkillIcon extends ChoosableIcon
{
	private Skill skill;

	public SkillIcon(ComponentContainer parent, Rect rect, Skill skill)
	{
		super(parent, rect);
		this.skill = skill;
	}

	// Getter
	@Override public int getChoosePhase() { return LobbyMenu.SKILL_PHASE; }
	@Override public ImageID getImageID()
	{
		if (skill == null || skill.getIconImageID() == null)
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		Debug.testLog("SkillIcon.getImageID() with skill " + skill.getClassName() + " has IconImageID (" + skill.getIconImageID().id + ", " + skill.getIconImageID().index + ")");
		return skill.getIconImageID();
	}
	public Skill getSkill() { return skill; }
}
