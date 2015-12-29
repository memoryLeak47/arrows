package entity.entities;

import java.util.LinkedList;

import static core.Main.DRAG;
import core.game.Game;
import core.game.ServerGame;
import entity.Entity;
import entity.entities.dynamic.SpinnableEntity;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import entity.entities.tile.ExtendedTile;
import graphics.Animation;
import misc.Debug;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;
import network.game.player.ServerGamePlayer;
import tilemap.GameTileMap;

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
		checkCollision();
		getPosition().add(getVelocity());
		getVelocity().scale(DRAG);
	}

	protected void onCollide(Entity e) {}

	protected void accelerate(GameVector p)
	{
		getVelocity().add(p);
	}

	protected void accelerate(float x, float y)
	{
		accelerate(new GameVector(x, y));
	}

	private void checkCollision()
	{
		Debug.test("checkCollision");
		for (Entity entity : getPossibleColliders())
		{
			if (isColliding(entity))
			{
				this.onCollide(entity);
			}
		}
	}

	protected boolean isColliding(Entity entity)
	{
		Debug.test("isColliding()");
		if (entity instanceof SpinnableEntity)
		{
			Debug.warn("DynamicEntity.isColliding(): Collision with SpinnableEntity TODO");
			return false;
		}
		else
		{
			if ((this.getRight() > entity.getLeft()) && (entity.getRight() > this.getLeft()))
			{
				if ((this.getTop() < entity.getBot()) && (this.getBot() > entity.getTop()))
				{
					return true;
				}
			}
		}
		return false;
	}

	// abstract

	protected abstract boolean isCollidingTiles();
	protected abstract boolean isCollidingPlayers();
	protected abstract boolean isCollidingBullets();

	// getter
	// gibt nur die Tiles zurück, die in der Range sind (mit denen man kollidieren könnte)
	protected final LinkedList<Entity> getPossibleColliders()
	{
		LinkedList<Entity> possibleColliders = new LinkedList<Entity>();

		if (isCollidingTiles())
		{
			for (ExtendedTile tile : GameTileMap.get().getPossibleColliderTiles(this))
			{
				possibleColliders.add(tile);
			}
		}
		if (isCollidingPlayers())
		{
			for (ServerGamePlayer player : ((ServerGame)Game.get()).getPlayers())
			{
				if (this != player)
				{
					possibleColliders.add(player);
				}
			}
		}
		if (isCollidingBullets())
		{
			for (ExtendedBullet bullet : ((ServerGame)Game.get()).getBullets())
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
