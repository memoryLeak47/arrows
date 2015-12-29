package entity.entities;

import static core.Main.DRAG;
import entity.Entity;
import graphics.Animation;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;

public abstract class DynamicEntity extends Entity
{
	private GameVector velocity = new GameVector();

	public DynamicEntity(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	@Override public void tick()
	{
		super.tick();
		getPosition().add(getVelocity());
		getVelocity().scale(DRAG);
	}

	protected void accelerate(GameVector p)
	{
		getVelocity().add(p);
	}

	protected void accelerate(float x, float y)
	{
		accelerate(new GameVector(x, y));
	}

	public GameVector getVelocity() { return velocity; }
}
