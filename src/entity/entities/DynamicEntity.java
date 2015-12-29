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

	// abstract
	protected abstract boolean isCollidingTiles();
	protected abstract boolean isCollidingPlayers();
	protected abstract boolean isCollidingBullets();

	// getter
	// gibt nur die Tiles zurück, die 
	protected final LinkedList<Entity> getPossibleColliders()
	{
		LinkedList<Entity> possibleColliders = new LinkedList<Entity>();

		if (isCollidingTiles())
		{
			for (ExtendedTile tile : GameTileMap.getPossibleColliders())
			{
				possibleColliders.add(tile);
			}
		}
		if (isCollidingPlayers())
		{
			for (ServerGamePlayer player : Game.get().getPlayers())
			{
				if (this != player)
				{
					possibleColliders.add(player);
				}
			}
		}
		if (isCollidingBullets())
		{
			for (ExtendedBullet bullet : Game.get().getBullets())
			{
				if (this != bullet)
				{
					possibleColliders.add(bullet);
				}
			}
		}
		return possibleColliders;
	}

	public GameVector getVelocity() { return velocity; }
}
