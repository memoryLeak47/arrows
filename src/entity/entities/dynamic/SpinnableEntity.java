package entity.entities.dynamic;

import entity.Entity;
import entity.entities.DynamicEntity;
import entity.entities.tile.ExtendedTile;
import graphics.Animation;
import misc.math.game.CollisionDetector;
import misc.math.game.GamePosition;
import misc.math.game.GameRect;
import misc.math.game.GameSize;

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

	/*
	@Override public GamePosition getTop() { }
	@Override public GamePosition getBot() { }
	@Override public GamePosition getRight() { }
	@Override public GamePosition getLeft() { }
	*/

	public GameRect getWrapper()
	{
		return new GameRect(
			getPosition(),
			new GameSize(
				Math.abs(getPosition().getX() - getLeft()),
				Math.abs(getPosition().getY() - getTop())));
	}
}
