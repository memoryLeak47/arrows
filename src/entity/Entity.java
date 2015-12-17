package entity;

import entity.entityparts.EffectEntityPart;
import entity.entityparts.LivingEntityPart;
import entity.entityparts.PhysicEntityPart;

import misc.Debug;
import misc.math.Rect;
import graphics.ImageID;
import misc.math.Position;

public abstract class Entity
{
	private LivingEntityPart livingEntityPart;
	private PhysicEntityPart physicEntityPart;
	private EffectEntityPart effectEntityPart;

	public Entity()
	{
		livingEntityPart = createLivingEntityPart();
		physicEntityPart = createPhysicEntityPart();
		effectEntityPart = createEffectEntityPart();
	}

	public void render()
	{
		Debug.warn("Entity.render(): TODO");
	}

	// Die 'create-Funktionen' werden in den Unterklassen überschrieben, um der Entity mitzuteilen, welche Entities benutzt werden
	protected LivingEntityPart createLivingEntityPart()
	{
		Debug.warn("Entity.createLivingEntity: Is not Overriden");
		return null;
	}

	protected PhysicEntityPart createPhysicEntityPart()
	{
		Debug.warn("Entity.createPhysicEntity: Is not Overriden");
		return null;
	}

	protected EffectEntityPart createEffectEntityPart()
	{
		Debug.warn("Entity.createEffectEntity: Is not Overriden");
		return null;
	}

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
		if (getPhysicEntityPart() != null)
		{
			return getPhysicEntityPart().getPosition();
		}
		Debug.warn("Entity.getPosition(): getPhysicEntityPart() == null");
		return new Position(0,0);
	}

	// Subentity getter
	public PhysicEntityPart getPhysicEntityPart()
	{
		Debug.warnIf(physicEntityPart == null, "Entity.getPhysicEntityPart(): returns null");
		return physicEntityPart;
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
