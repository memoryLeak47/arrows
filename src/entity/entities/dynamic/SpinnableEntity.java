package entity.entities.dynamic;

import entity.Entity;
import entity.entities.DynamicEntity;
import entity.entities.tile.ExtendedTile;
import graphics.Animation;
import misc.math.game.CollisionDetector;
import misc.math.game.GamePosition;

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

	protected float getRotation() { return rotation; }
}
