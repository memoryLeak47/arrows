package entity.part.parts.living;

import entity.Entity;
import entity.part.LivingEntityPart;
import entity.part.property.properties.living.MortalLivingEntityPartProperty;
import entity.part.property.properties.living.GraphicalLivingEntityPartProperty;
import misc.game.Team;
import playerproperty.avatar.Avatar;
import playerproperty.item.Item;
import playerproperty.skill.Skill;
import misc.game.kill.KDCounter;
import misc.game.PlayerStats;

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

	public String getName() { return name; }
	public int getRank() { return rank; }
	public Team getTeam() { return team; }
	public Avatar getAvatar() { return avatar; }
	public Skill[] getSkills() { return skills; }
	public Item[] getItems() { return items; }
	public PlayerStats getPlayerStats() { return playerStats; }
	public short[] getCharges() { return charges; }
	public KDCounter getKdCounter() { return kdCounter; }

	public void setName(String name) { this.name = name; }
	public void setRank(int rank) { this.rank = rank; }
	public void setTeam(Team team) { this.team = team; }
	public void setAvatar(Avatar avatar) { this.avatar = avatar; }
	public void setSkills(Skill[] skills) { this.skills = skills; }
	public void setItems(Item[] items) { this.items = items; }
}
