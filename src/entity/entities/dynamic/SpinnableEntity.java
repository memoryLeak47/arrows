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
		// Vektor nach rechts, mit halbem Durchmesser als Länge
		GameVector vec = new GameVector(getSize().getMagnitude()/2.f, 0);

		// Vektor von Mittepunkt in eine Ecke
		vec = vec.rotate(getRotation());

		// Mittelpunkts y-Position - Betrag von Vektors y-Position --> höchste Stelle
		return (-Math.abs(vec.getY())) + getPosition().getY();
	}

	@Override public float getBot()
	{
		GameVector vec = new GameVector(getSize().getMagnitude()/2.f, 0);
		vec = vec.rotate(getRotation());
		return Math.abs(vec.getY()) + getPosition().getY();
	}

	@Override public float getRight()
	{
		GameVector vec = new GameVector(getSize().getMagnitude()/2.f, 0);
		vec = vec.rotate(getRotation());
		return Math.abs(vec.getX()) + getPosition().getX();
	}

	@Override public float getLeft()
	{
		GameVector vec = new GameVector(getSize().getMagnitude()/2.f, 0);
		vec = vec.rotate(getRotation());
		return (-Math.abs(vec.getX())) + getPosition().getX();
	}

	@Override public MinimizedEntity toMinimizedEntity()
	{
		return new MinimizedSpinnableEntity(getPosition(), getImageID(), getRotation(), Effect.toEffectIDs(getEffects()));
	}

	public GameRect getWrapper()
	{
		return new GameRect(
			getPosition(),
			new GameSize(
				Math.abs(getPosition().getX() - getLeft()),
				Math.abs(getPosition().getY() - getTop())));
	}
}
