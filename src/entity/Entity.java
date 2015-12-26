package entity;

import entity.part.EffectEntityPart;
import entity.part.LivingEntityPart;
import entity.part.PhysicsEntityPart;

import misc.Debug;
import misc.math.menu.MenuRect;
import graphics.ImageID;
import misc.math.game.GamePosition;

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

	public ImageID getImageID()
	{
		if (getLivingEntityPart() != null)
		{
			return getLivingEntityPart().getImageID();
		}
		Debug.warn("Entity.getImageID(): getLivingEntityPart() == null");
		return null;
	}

	public GamePosition getPosition()
	{
		if (getPhysicsEntityPart() != null)
		{
			return getPhysicsEntityPart().getPosition();
		}
		Debug.warn("Entity.getPosition(): getPhysicsEntityPart() == null");
		return new GamePosition(0,0);
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
