package entity.entities.dynamic.spinnable.bullet;

import damage.Damage;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import entity.Entity;
import graphics.Animation;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;
import player.ServerGamePlayer;

public abstract class StickyBullet extends ExtendedBullet
{
	private Entity target = null;
	private GameVector distanceToTarget;
	private int counter = getInitialCounterValue();
	private boolean hasCollided = false;

	public StickyBullet(ServerGamePlayer owner, GamePosition position, Animation animation, GameVector velocity)
	{
		super(owner, position, animation, velocity);
	}

	@Override public void onCollide(Entity e)
	{
		if (e == getOwner())
		{
			return;
		}
		target = e;
		distanceToTarget = GameVector.getFromTo(getPosition(), e.getPosition());
		if (!hasCollided)
		{
			e.onDamage(getDamage());
		}
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
