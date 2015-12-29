package entity.entities.dynamic.mob;

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

	public int getHealth() { return health; }
}
