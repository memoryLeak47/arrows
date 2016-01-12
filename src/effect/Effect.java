package effect;

import java.util.LinkedList;

import effect.effects.*;
import entity.Entity;
import graphics.ImageID;
import misc.Debug;

public abstract class Effect implements Cloneable
{
	public static int EFFECTS_SIZE;

	private static Effect[] staticEffects;
	private static boolean initPhase = true;

	public static final int BURN_EFFECT = 0;

	static
	{
		staticEffects = new Effect[]
		{
			new BurnEffect()
			// add effects here
		};

		for (int i = 0; i < staticEffects.length; i++)
			staticEffects[i].id = i;

		EFFECTS_SIZE = staticEffects.length;

		initPhase = false;
	}

	private Entity owner;
	private int id;
	private short[] properties;

	protected Effect()
	{
		if (!initPhase)
		{
			Debug.warn("invalid creation of an Effect, create it with getEffectByMinimizedEffect(new MinimizedEffect(<id>, <stats>))");
		}
	}

	public MinimizedEffect toMinimizedEffect()
	{
		return new MinimizedEffect(getID(), getProperties());
	}

	public int getID()
	{
		return id;
	}

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
				list.add(getByID(i));
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
		Effect tmp = null;
		try
		{
			tmp = (Effect) staticEffects[effect.getEffectID()].clone();
		} catch (Exception e)
		{
			Debug.error("Effect.getEffectByMinimizedEffect: can't clone effect with id " + effect.getEffectID());
		}
		tmp.setProperties(effect.getProperties());
		return tmp;
	}

	public abstract ImageID getImageID();

	// needed for ClientGamePlayer, who has to handle EffectsOnOff by the ID
	public static Effect getByID(int id)
	{
		return staticEffects[id];
	}

	public static Effect createByID(int id)
	{
		try
		{
			return (Effect) staticEffects[id].clone();
		} catch (Exception e)
		{
			Debug.error("Effect.getEffectByID: can't clone effect with id " + id);
		}
		return null;
	}

	public void tick() {}

	public final void setOwner(Entity e)
	{
		owner = e;
	}

	public final Entity getOwner()
	{
		return owner;
	}

	public Effect copy()
	{
		try
		{
			return (Effect) this.clone();
		} catch (Exception e)
		{
			Debug.error("Effect.copy: can't clone effect " + this);
		}
		return null;
	}

	public short[] getProperties() { return properties; }
}
