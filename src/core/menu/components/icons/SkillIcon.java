package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
import game.skill.Skill;
import graphics.ImageID;
import misc.math.Rect;

public class SkillIcon extends Icon
{
	private Skill skill;

	public SkillIcon(ComponentContainer parent, Rect rect, Skill skill)
	{
		super(parent, rect);
		this.skill = skill;
	}

	@Override public ImageID getImageID()
	{
		return skill.getIconImageID();
	}
}
