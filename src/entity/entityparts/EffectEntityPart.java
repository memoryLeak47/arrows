package entity.entityparts;

import entity.Entity;
import entity.EntityPart;
import misc.Debug;

public abstract class EffectEntityPart extends EntityPart
{
	public EffectEntityPart(Entity parent)
	{
		super(parent);
		Debug.warn("EffectEntityPart.Constructor(): TODO");
	}
}
