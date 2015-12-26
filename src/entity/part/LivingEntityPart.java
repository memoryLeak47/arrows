package entity.part;

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
		Debug.warnIf(animation == null, "LivingEntityPart.getImageID(): animation == null");
		if (animation != null)
		{
			Debug.warnIf(animation.getImageID() == null, "LivingEntityPart.getImageID(): animation.getImageID() == null");
			return animation.getImageID();
		}
	}
}
