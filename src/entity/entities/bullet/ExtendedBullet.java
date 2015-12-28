package entity.entities.bullet;

import entity.Entity;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class ExtendedBullet extends Entity
{
	public ExtendedBullet(GamePosition position, Animation animation)
	{
		super(position, animation);
	}
}
