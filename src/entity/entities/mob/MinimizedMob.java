package entity.entities.mob;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedMob extends MinimizedEntity
{
	private int health;

	public MinimizedMob(ImageID imageID, GamePosition position, int health /*, Effects*/)
	{
		super(imageID, position);
		this.health = health;
	}

	@Override public void render()
	{
		Debug.warn("MinimizedMob.render(): TODO");
	}

	public int getHealth() { return health; }
}
