package network.game.player;

import entity.MinimizedEntity;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedGamePlayer extends MinimizedEntity
{
	private int health;
	private String name;

	public MinimizedGamePlayer(ImageID imageID, GamePosition position, String name, int health /*, Effects TODO*/)
	{
		super(imageID, position);
		this.health = health;
		this.name = name;
	}

	public String getName() { return name; }
	public int getHealth() { return health; }
}
