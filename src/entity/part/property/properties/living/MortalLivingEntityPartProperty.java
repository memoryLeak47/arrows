package entity.part.property.properties.living;

import entity.part.property.LivingEntityPartProperty;

public interface MortalLivingEntityPartProperty extends LivingEntityPartProperty
{
	public void die();
	public int getHealth();
}
