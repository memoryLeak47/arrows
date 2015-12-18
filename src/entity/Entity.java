package entity;

import entity.entitypart.EffectEntityPart;
import entity.entitypart.LivingEntityPart;
import entity.entitypart.PhysicsEntityPart;

import misc.Debug;
import misc.math.Rect;
import graphics.ImageID;
import misc.math.Position;

public abstract class Entity
{
	private LivingEntityPart livingEntityPart;
	private PhysicsEntityPart physicsEntityPart;
	private EffectEntityPart effectEntityPart;

	public Entity()
	{
		livingEntityPart = createLivingEntityPart();
		physicsEntityPart = createPhysicsEntityPart();
		effectEntityPart = createEffectEntityPart();
	}

	public void render()
	{
		Debug.warn("Entity.render(): TODO");
	}

	// Die 'create-Funktionen' werden in den Unterklassen überschrieben, um der Entity mitzuteilen, welche Entities benutzt werden
	protected abstract LivingEntityPart createLivingEntityPart();
	protected abstract PhysicsEntityPart createPhysicsEntityPart();
	protected abstract EffectEntityPart createEffectEntityPart();

	// Getter
	public int getHealth()
	{
		if (getLivingEntityPart() != null)
		{
			return getLivingEntityPart().getHealth();
		}
		Debug.warn("Entity.getHealth(): getLivingEntityPart() == null");
		return 0;
	}

	public ImageID getImageID()
	{
		if (getLivingEntityPart() != null)
		{
			return getLivingEntityPart().getImageID();
		}
		Debug.warn("Entity.getImageID(): getLivingEntityPart() == null");
		return null;
	}

	public Position getPosition()
	{
		if (getPhysicsEntityPart() != null)
		{
			return getPhysicsEntityPart().getPosition();
		}
		Debug.warn("Entity.getPosition(): getPhysicsEntityPart() == null");
		return new Position(0,0);
	}

	// Subentity getter
	public PhysicsEntityPart getPhysicsEntityPart()
	{
		Debug.warnIf(physicsEntityPart == null, "Entity.getPhysicsEntityPart(): returns null");
		return physicsEntityPart;
	}

	public EffectEntityPart getEffectEntityPart()
	{
		Debug.warnIf(effectEntityPart == null, "Entity.getEffectEntityPart(): returns null");
		return effectEntityPart;
	}

	public LivingEntityPart getLivingEntityPart()
	{
		Debug.warnIf(livingEntityPart == null, "Entity.getLivingEntityPart(): returns null");
		return livingEntityPart;
	}
}
