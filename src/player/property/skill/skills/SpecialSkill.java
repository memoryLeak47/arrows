package player.property.skill.skills;

import player.property.skill.Skill;
import graphics.Animation;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.ServerGamePlayer;

public abstract class SpecialSkill extends Skill
{
	public SpecialSkill(byte avatarID)
	{
		super(avatarID);
	}

}
