/*
	
*/
package network.game.player;

import java.util.LinkedList;

import entity.Entity;
import graphics.ImageID;
import misc.game.Team;
import misc.game.kill.KDCounter;
import misc.math.Position;
import network.lobby.LobbyPlayer;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;

public class ClientGamePlayer implements GamePlayer
{
	private String name;
	private int rank;
	private Team team;

	// Player Properties
	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private KDCounter kdCounter = new KDCounter();
	private LinkedList<Integer> effectIDs = new LinkedList<Integer>();
	private Position position;
	private int health;
	private ImageID imageID;

	public ClientGamePlayer(LobbyPlayer player)
	{
		name = player.getName();
		rank = player.getRank();
		avatar = player.getAvatar();
		team = player.getTeam();
		skills = player.getSkills();
		items = player.getItems();
	}

	public void apply(ClientGamePlayerFrameUpdate update)
	{
		setHealth(update.getHealth());
		setPosition(update.getPosition());
		setImageID(update.getImageID());
	}

	// setter

	private void setHealth(int health) { this.health = health; }
	private void setPosition(Position pos) { this.position = new Position(pos); }
	private void setImageID(ImageID id) { this.imageID = new ImageID(id); }

	// getter

	@Override public String getName() { return name; }
	public int getRank() { return rank; }
	@Override public Team getTeam() { return team; }

	public Avatar getAvatar() { return avatar; }
	public Skill[] getSkills() { return skills; }
	public Item[] getItems() { return items; }

	public KDCounter getKDCounter() { return kdCounter; }
	@Override public LinkedList<Integer> getEffectIDs() { return effectIDs; }
	public Position getPosition() { return position; }
	@Override public int getHealth() { return health; }
	@Override public ImageID getImageID() { return imageID; }
}
