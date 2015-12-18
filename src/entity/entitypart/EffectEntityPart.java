package entity.entitypart;

import java.util.LinkedList;

import entity.Entity;
import entity.EntityPart;
import misc.Debug;
import misc.game.effect.Effect;

public abstract class EffectEntityPart extends EntityPart
{
	private LinkedList<Effect> effects = new LinkedList<Effect>();

	public EffectEntityPart(Entity parent)
	{
		super(parent);
		Debug.warn("EffectEntityPart.Constructor(): TODO");
	}

	public void applyEffect(Effect effect)
	{
		Debug.warnIf(getValidEffectIDs().length <= effect.getID(), "EffectEntityPart.applyEffect: EffectID out of getValidEffectIDs() range");
		if (getValidEffectIDs()[effect.getID()])
		{
			effects.add(effect);
		}
	}

	public boolean[] getValidEffectIDs()
	{
		return new boolean[]
		{
			true // BurnEffect
		};
	}
}
