package entity.entities;

import static core.Main.DRAG;
import entity.Entity;
import graphics.Animation;
import misc.math.game.GamePoint;
import misc.math.game.GamePosition;

public abstract class DynamicEntity extends Entity
{
	private GamePoint velocity = new GamePoint();

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

	protected void accelerate(GamePoint p)
	{
		getVelocity().add(p);
	}

	protected void accelerate(float x, float y)
	{
		accelerate(new GamePoint(x, y));
	}

	public GamePoint getVelocity() { return velocity; }
}
