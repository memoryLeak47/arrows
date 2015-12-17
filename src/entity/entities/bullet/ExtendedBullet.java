package entity.entities.bullet;

import entity.Entity;
import entity.entityparts.EffectEntityPart;
import entity.entityparts.LivingEntityPart;
import entity.entityparts.PhysicsEntityPart;
import misc.Debug;

public abstract class ExtendedBullet extends Entity
{
	@Override public PhysicsEntityPart createPhysicsEntityPart()
	{
		Debug.warn("ExtendedBullet.createPhysicsEntityPart(): TODO");
		return null;
	}

	@Override public LivingEntityPart createLivingEntityPart()
	{
		Debug.warn("ExtendedBullet.createLivingEntityPart(): TODO");
		return null;
	}

	@Override public EffectEntityPart createEffectEntityPart()
	{
		Debug.warn("ExtendedBullet.createEffectEntityPart(): TODO");
		return null;
	}
}
