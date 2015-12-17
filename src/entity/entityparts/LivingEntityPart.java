package entity.entityparts;

import graphics.ImageID;
import entity.Entity;
import entity.EntityPart;
import misc.Debug;

public class LivingEntityPart extends EntityPart
{
	private int health;

	public LivingEntityPart(Entity parent, int health)
	{
		super(parent);
		this.health = health;
		Debug.warn("LivingEntityPart.Constructor(): TODO)");
	}

	public int getHealth()
	{
		return health;
	}

	public ImageID getImageID()
	{
		Debug.warn("LivingEntityPart.getImageID(): TODO");
		return null;
	}
}
