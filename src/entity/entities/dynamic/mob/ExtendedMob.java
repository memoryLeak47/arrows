package entity.entities.dynamic.mob;

import entity.entities.DynamicEntity;
import graphics.Animation;
import misc.math.game.GamePosition;

public abstract class ExtendedMob extends DynamicEntity
{
	public ExtendedMob(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

}
