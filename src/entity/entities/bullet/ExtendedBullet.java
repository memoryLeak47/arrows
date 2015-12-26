package entity.entities.bullet;

import entity.Entity;
import entity.part.EffectEntityPart;
import entity.part.LivingEntityPart;
import entity.part.PhysicsEntityPart;
import entity.part.parts.physics.DynamicPhysicsEntityPart;
import misc.Debug;
import misc.math.menu.MenuPosition;

public abstract class ExtendedBullet extends Entity
{
	@Override public PhysicsEntityPart createPhysicsEntityPart()
	{
		return new DynamicPhysicsEntityPart(this);
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
