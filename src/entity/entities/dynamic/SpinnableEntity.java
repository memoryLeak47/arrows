package entity.entities.dynamic;

import effect.Effect;
import entity.Entity;
import entity.MinimizedEntity;
import entity.entities.DynamicEntity;
import entity.entities.dynamic.spinnable.MinimizedSpinnableEntity;
import entity.entities.tile.ExtendedTile;
import graphics.Animation;
import misc.math.collision.CollisionDetector;
import misc.math.game.GamePosition;
import misc.math.game.GameRect;
import misc.math.game.GameSize;
import misc.math.game.GameVector;

public abstract class SpinnableEntity extends DynamicEntity
{
	private float rotation;

	public SpinnableEntity(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override protected final boolean isColliding(Entity entity)
	{
		return CollisionDetector.areCollidingSpinnable(this, entity);
	}

	protected final void updateRotationByVelocity()
	{
		if (getVelocity().getMagnitude() != 0)
		{
			setRotation((float)-(Math.atan2(0, 1) - Math.atan2(getVelocity().getY(), getVelocity().getX())));
		}
	}

	private final void setRotation(float rotation)
	{
		this.rotation = rotation;
	}

	public float getRotation() { return rotation; }

	@Override public float getTop()
	{
		return getPosition().getY() - getSize().getMagnitude()/2.f; // too high
	}

	@Override public float getBot()
	{
		return getPosition().getY() + getSize().getMagnitude()/2.f; // too low
	}

	@Override public float getRight()
	{
		return getPosition().getX() + getSize().getMagnitude()/2.f; // too right
	}

	@Override public float getLeft()
	{
		return getPosition().getX() - getSize().getMagnitude()/2.f; // too left
	}

	@Override public MinimizedEntity toMinimizedEntity()
	{
		return new MinimizedSpinnableEntity(getPosition(), getImageID(), getRotation(), Effect.toEffectIDs(getEffects()));
	}

	@Override public GameRect getWrapper()
	{
		return new GameRect(
			getPosition(),
			new GameSize(
				Math.abs(getPosition().getX() - getLeft()),
				Math.abs(getPosition().getY() - getTop())));
	}
}
