package entity.entitypart;

import graphics.Animation;
import graphics.ImageID;
import entity.Entity;
import entity.EntityPart;
import misc.Debug;

public abstract class LivingEntityPart extends EntityPart
{
	private Animation animation; // TODO may be put in EntityPartProperty

	public LivingEntityPart(Entity parent)
	{
		super(parent);
	}

	public ImageID getImageID() // TODO may be put in EntityPartProperty
	{
		Debug.warn("LivingEntityPart.getImageID(): TODO");
		return null;
	}
}
