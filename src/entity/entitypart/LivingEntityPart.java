package entity.entitypart;

import graphics.Animation;
import graphics.ImageID;
import entity.Entity;
import entity.EntityPart;
import misc.Debug;

public abstract class LivingEntityPart extends EntityPart
{
	private Animation animation;
	private int health;

	public LivingEntityPart(Entity parent)
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
