package effect;

import java.util.LinkedList;

import effect.effects.*;
import entity.Entity;
import graphics.ImageID;
import misc.Debug;

public abstract class Effect implements Cloneable
{
	public static final int EFFECTS_SIZE;

	private static EffectCreator[] effectCreators;

	public static final int BURN_ID = 0;

	static
	{
		effectCreators = new EffectCreator[]
		{
			new EffectCreator() { public Effect create() { return new BurnEffect(); }}
			// add effects here
		};

		EFFECTS_SIZE = effectCreators.length;
	}

	private Entity target;
	private short[] properties;

	public MinimizedEffect toMinimizedEffect()
	{
		return new MinimizedEffect(getID(), getProperties());
	}

	public abstract int getID();

	public static LinkedList<MinimizedEffect> toMinimizedEffects(LinkedList<Effect> effects)
	{
		LinkedList<MinimizedEffect> miniEffects = new LinkedList<MinimizedEffect>();
		for (Effect e : effects)
		{
			miniEffects.add(e.toMinimizedEffect());
		}
		return miniEffects;
	}

	// schreibt die Effekte in eine boolean Array
	public static boolean[] toEffectIDs(LinkedList<Effect> effects)
	{
		boolean[] bools = new boolean[EFFECTS_SIZE];
		for (Effect e : effects)
		{
			bools[e.getID()] = true;
		}
		return bools;
	}

	public static LinkedList<Effect> getEffectsByBools(boolean[] bools)
	{
		LinkedList<Effect> list = new LinkedList<Effect>();
		for (int i = 0; i < bools.length; i++)
		{
			if (bools[i])
			{
				list.add(createByID(i));
			}
		}
		return list;
	}

	public static MinimizedEffect getMinimizedEffectByID(int id)
	{
		return new MinimizedEffect(id, new short[0]);
	}

	protected void setProperties(short[] properties)
	{
		this.properties = new short[properties.length];
		for (int i = 0; i < properties.length; i++)
		{
			this.properties[i] = properties[i];
		}
	}

	// needed for ClientGamePlayer/LocalClientGamePlayer to uncompress the MinimizedEffect
	public static Effect getEffectByMinimizedEffect(MinimizedEffect effect)
	{
		Debug.warnIf(effect == null, "Effect.getEffectByMinimizedEffect(null)");
		Effect e = createByID(effect.getEffectID());
		e.setProperties(effect.getProperties());
		return e;
	}

	public abstract ImageID getImageID();

	// needed for ClientGamePlayer, who has to handle EffectsOnOff by the ID
	public static Effect createByID(int id)
	{
		return effectCreators[id].create();
	}

	public abstract Effect copy();
	public boolean isSpreading() { return false; }

	public void tick() {}

	public final void setTarget(Entity e)
	{
		target = e;
	}

	public final Entity getTarget()
	{
		return target;
	}

	public short[] getProperties() { return properties; }

	public boolean hasToBeRemoved() { return false; }
}
