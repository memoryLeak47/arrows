package misc.game.effect;

import java.util.LinkedList;

import misc.Debug;
import misc.game.effect.effects.*;

public abstract class Effect implements Cloneable
{
	private static Effect[] staticEffects;

	static
	{
		staticEffects = new Effect[]
		{
			new BurnEffect()
			// add effects here
		};

		for (int i = 0; i < staticEffects.length; i++)
			staticEffects[i].id = i;
	}

	private int id;
	private short[] properties;

	protected Effect() {}

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

	public static LinkedList<Integer> toEffectIDs(LinkedList<Effect> effects)
	{
		LinkedList<Integer> miniEffects = new LinkedList<Integer>();
		for (Effect e : effects)
		{
			miniEffects.add(e.getID());
		}
		return miniEffects;
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
		} catch (Exception e) { Debug.error("Effect.getEffectByMinimizedEffect: can't clone effect with id " + effect.getEffectID()); }
		tmp.setProperties(effect.getProperties());
		return tmp;
	}

	// needed for ClientGamePlayer, who has to handle EffectsOnOff by the ID
	public static Effect getEffectByID(int id)
	{
		return staticEffects[id];
	}

	public short[] getProperties() { return properties; }
}
