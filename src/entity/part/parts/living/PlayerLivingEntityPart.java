package entity.part.parts.living;

import entity.Entity;
import entity.part.LivingEntityPart;
import entity.part.property.properties.living.MortalLivingEntityPartProperty;
import entity.part.property.properties.living.GraphicalLivingEntityPartProperty;

public class PlayerLivingEntityPart extends LivingEntityPart implements MortalLivingEntityPartProperty, GraphicalLivingEntityPartProperty
{
	int health;

	public PlayerLivingEntityPart(Entity parent)
	{
		super(parent);
	}

	@Override public int getHealth() { return health; }
	@Override public void die() { /*TODO*/ }
}
