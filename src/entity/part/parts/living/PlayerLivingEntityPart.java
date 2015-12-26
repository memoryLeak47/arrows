package entity.part.parts.living;

import entity.Entity;
import entity.part.LivingEntityPart;
import entity.part.property.properties.living.MortalLivingEntityPartProperty;
import entity.part.property.properties.living.GraphicalLivingEntityPartProperty;

public class PlayerLivingEntityPart extends LivingEntityPart implements MortalLivingEntityPartProperty, GraphicalLivingEntityPartProperty
{
	private int health;

	private String name;
	private int rank;
	private Team team;

	// PlayerProperties
	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private PlayerStats playerStats;
	private short[] charges;

	private KDCounter kdCounter = new KDCounter();


	public PlayerLivingEntityPart(Entity parent)
	{
		super(parent);
	}

	@Override public int getHealth() { return health; }
	@Override public void die() { /*TODO*/ }
}
