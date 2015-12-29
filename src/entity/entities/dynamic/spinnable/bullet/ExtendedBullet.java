package entity.entities.dynamic.spinnable.bullet;

import entity.entities.dynamic.SpinnableEntity;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class ExtendedBullet extends SpinnableEntity
{
	public ExtendedBullet(GamePosition position, Animation animation)
	{
		super(position, animation);
	}
}
