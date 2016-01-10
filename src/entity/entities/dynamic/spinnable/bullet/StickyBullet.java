package entity.entities.dynamic.spinnable.bullet;

import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import entity.Entity;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;
import graphics.Animation;

public abstract class StickyBullet extends ExtendedBullet
{
	private Entity target = null;
	private GameVector distanceToTarget;
	private int counter = getInitialCounterValue();
	private boolean hasCollided = false;

	public StickyBullet(GamePosition position, Animation animation, GameVector velocity)
	{
		super(position, animation, velocity);
	}

	@Override public void onCollide(Entity e)
	{
		target = e;
		distanceToTarget = GameVector.getFromTo(getPosition(), e.getPosition());
		hasCollided = true;
		stop();
	}

	@Override public void tick()
	{
		super.tick();
		if (target != null)
		{
			if (target.hasToBeRemoved())
			{
				target = null;
				counter = getInitialCounterValue();
			}
			else
			{
				setPosition(target.getPosition().minus(distanceToTarget));
			}
		}

		if (hasCollided)
		{
			counter--;
		}
	}

	protected int getInitialCounterValue() { return 20; }
	@Override public boolean hasToBeRemoved() { return counter <= 0; }
}
