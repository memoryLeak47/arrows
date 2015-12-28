package entity.entities.mob;

import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePosition;

public abstract class ExtendedMob extends Entity
{
	public ExtendedMob(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

}
