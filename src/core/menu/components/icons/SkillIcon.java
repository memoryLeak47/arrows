package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
//import game.skill.SkillInfo;
//import game.graphics.ImageID;
import misc.math.Rect;

public class SkillIcon extends Icon
{
	private int skillInfo; // TODO: int avatarinfo -> AvatarInfo avatarInfo

	public SkillIcon(ComponentContainer parent, Rect rect, int skillInfo)
	{
		super(parent, rect);
		this.skillInfo = skillInfo;
	}

	@Override public int getImageID() // TODO: int getImageID() -> ImageID getImageID()
	{
		return skillInfo;
	}
}
