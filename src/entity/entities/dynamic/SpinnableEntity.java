package entity.entities.dynamic;

import effect.Effect;
import entity.Entity;
import entity.MinimizedEntity;
import entity.entities.DynamicEntity;
import entity.entities.dynamic.spinnable.MinimizedSpinnableEntity;
import tile.ExtendedTile;
import graphics.Animation;
import misc.Debug;
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
		GameVector vec = null;
		float rotation = getRotation();
		if (rotation < 0)
		{
			rotation += Math.PI*2.f;
		}

		if ((rotation >= 0) && (rotation < (Math.PI/2.f))) // 				0° < Rotation < 90° 	->	Der Punkt links oben ist der Höchste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getTop())); // Vector vom Mittelpunkt zum Punkt links oben erstellen
		}
		else if ((rotation >= (Math.PI/2.f)) && (rotation < (Math.PI))) // 		90° < Rotation < 180° 	->	Der Punkt links unten ist der Höchste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getBot())); // Vector vom Mittelpunkt zum Punkt links unten erstellen
		}
		else if ((rotation >= (Math.PI)) && (rotation < (Math.PI*3.f/2.f))) //	 	180° < Rotation < 270° 	->	Der Punkt rechts unten ist der Höchste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getBot())); // Vector vom Mittelpunkt zum Punkt rechts unten erstellen
		}
		else if ((rotation >= (Math.PI*3.f/2.f)) && (rotation < (Math.PI*2.f))) // 	270° < Rotation < 360° 	->	Der Punkt rechts oben ist der Höchste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getTop())); // Vector vom Mittelpunkt zum Punkt rechts oben erstellen
		}
		else
		{
			Debug.error("SpinnableEntity.getTop(): invalid Rotation ( " + rotation + ") = ( " + (rotation * 180.f / Math.PI) + "° )");
		}
		vec = vec.rotate(rotation); // Vector drehen
		return getPosition().getY() + vec.getY();
	}

	@Override public float getBot()
	{
		GameVector vec = null;
		float rotation = getRotation();
		if (rotation < 0)
		{
			rotation += Math.PI*2.f;
		}

		if ((rotation >= 0) && (rotation < (Math.PI/2.f))) // 				0° < Rotation < 90° 	->	Der Punkt rechts unten ist der Unterste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getBot())); // Vector vom Mittelpunkt zum Punkt rechts unten erstellen
		}
		else if ((rotation >= (Math.PI/2.f)) && (rotation < (Math.PI))) // 		90° < Rotation < 180° 	->	Der Punkt rechts oben ist der Unterste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getTop())); // Vector vom Mittelpunkt zum Punkt rechts oben erstellen
		}
		else if ((rotation >= (Math.PI)) && (rotation < (Math.PI*3.f/2.f))) //	 	180° < Rotation < 270° 	->	Der Punkt links oben ist der Unterste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getTop())); // Vector vom Mittelpunkt zum Punkt links oben erstellen
		}
		else if ((rotation >= (Math.PI*3.f/2.f)) && (rotation < (Math.PI*2.f))) // 	270° < Rotation < 360° 	->	Der Punkt links unten ist der Unterste. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getBot())); // Vector vom Mittelpunkt zum Punkt links unten erstellen
		}
		else
		{
			Debug.error("SpinnableEntity.getTop(): invalid Rotation ( " + rotation + ") = ( " + (rotation * 180.f / Math.PI) + "° )");
		}
		vec = vec.rotate(rotation); // Vector drehen
		return getPosition().getY() + vec.getY();
	}

	@Override public float getRight()
	{
		GameVector vec = null;
		float rotation = getRotation();
		if (rotation < 0)
		{
			rotation += Math.PI*2.f;
		}

		if ((rotation >= 0) && (rotation < (Math.PI/2.f))) // 				0° < Rotation < 90° 	->	Der Punkt rechts oben ist der am weitesten Rechts. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getTop())); // Vector vom Mittelpunkt zum Punkt rechts oben erstellen
		}
		else if ((rotation >= (Math.PI/2.f)) && (rotation < (Math.PI))) // 		90° < Rotation < 180° 	->	Der Punkt links oben ist der am weitesten Rechts. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getTop())); // Vector vom Mittelpunkt zum Punkt links oben erstellen
		}
		else if ((rotation >= (Math.PI)) && (rotation < (Math.PI*3.f/2.f))) //	 	180° < Rotation < 270° 	->	Der Punkt links unten ist der am weitesten Rechts. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getBot())); // Vector vom Mittelpunkt zum Punkt links unten erstellen
		}
		else if ((rotation >= (Math.PI*3.f/2.f)) && (rotation < (Math.PI*2.f))) // 	270° < Rotation < 360° 	->	Der Punkt rechts unten ist der am weitesten Rechts. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getBot())); // Vector vom Mittelpunkt zum Punkt rechts unten erstellen
		}
		else
		{
			Debug.error("SpinnableEntity.getTop(): invalid Rotation ( " + rotation + ") = ( " + (rotation * 180.f / Math.PI) + "° )");
		}
		vec = vec.rotate(rotation); // Vector drehen
		return getPosition().getX() + vec.getX();
	}

	@Override public float getLeft()
	{
		GameVector vec = null;
		float rotation = getRotation();
		if (rotation < 0)
		{
			rotation += Math.PI*2.f;
		}

		if ((rotation >= 0) && (rotation < (Math.PI/2.f))) // 				0° < Rotation < 90° 	->	Der Punkt links unten ist der am weitesten Links. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getBot())); // Vector vom Mittelpunkt zum Punkt links unten erstellen
		}
		else if ((rotation >= (Math.PI/2.f)) && (rotation < (Math.PI))) // 		90° < Rotation < 180° 	->	Der Punkt unten rechts ist der am weitesten Links. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getBot())); // Vector vom Mittelpunkt zum Punkt unten rechts erstellen
		}
		else if ((rotation >= (Math.PI)) && (rotation < (Math.PI*3.f/2.f))) //	 	180° < Rotation < 270° 	->	Der Punkt oben rechts ist der am weitesten Links. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getRight(), super.getTop())); // Vector vom Mittelpunkt zum Punkt oben rechts erstellen
		}
		else if ((rotation >= (Math.PI*3.f/2.f)) && (rotation < (Math.PI*2.f))) // 	270° < Rotation < 360° 	->	Der Punkt oben links ist der am weitesten Links. 
		{
			vec = GameVector.getFromTo(getPosition(), new GameVector(super.getLeft(), super.getTop())); // Vector vom Mittelpunkt zum Punkt oben links erstellen
		}
		else
		{
			Debug.error("SpinnableEntity.getTop(): invalid Rotation ( " + rotation + ") = ( " + (rotation * 180.f / Math.PI) + "° )");
		}
		vec = vec.rotate(rotation); // Vector drehen
		return getPosition().getX() + vec.getX();
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
