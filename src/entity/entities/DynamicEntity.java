package entity.entities;

import java.util.LinkedList;

import static core.Main.DRAG;
import core.game.Game;
import core.game.ServerGame;
import entity.Entity;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import entity.entities.tile.ExtendedTile;
import graphics.Animation;
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
			/*
			for (ExtendedTile tile : GameTileMap.get().getPossibleColliderTiles(this))
			{
				possibleColliders.add(tile);
			}*/
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
