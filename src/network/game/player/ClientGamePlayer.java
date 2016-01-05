/*
	Alle externen Player des Clients sind von der Klasse ClientGamePlayer.
	Diese werden durch ClientGamePlayerFrameUpdate geupdated (apply-Funktion).
*/

package network.game.player;

import java.util.LinkedList;

import entity.Entity;
import entity.MinimizedEntity;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.game.Team;
import misc.game.kill.KDCounter;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import network.lobby.LobbyPlayer;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;

public class ClientGamePlayer extends MinimizedEntity implements GamePlayer
{
	// TODO speichern, ob er am Leben ist!
	private String name;
	private int rank;
	private Team team;

	// Player Properties
	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private KDCounter kdCounter = new KDCounter();
	private LinkedList<Integer> effectIDs = new LinkedList<Integer>();
	private int health;

	public ClientGamePlayer(LobbyPlayer player)
	{
		super(new GamePosition(), ImageFile.VOID_ICON.getImageID());
		name = player.getName();
		rank = player.getRank();
		avatar = player.getAvatar();
		team = player.getTeam();
		skills = player.getSkills();
		items = player.getItems();
	}

	public void apply(ClientGamePlayerFrameUpdate update)
	{
		health = update.getHealth();
		setPosition(update.getPosition());
		setImageID(update.getImageID());
	}

	// getter
	@Override public String getName() { return name; }
	public int getRank() { return rank; }
	@Override public Team getTeam() { return team; }

	public Avatar getAvatar() { return avatar; }
	public Skill[] getSkills() { return skills; }
	public Item[] getItems() { return items; }

	public KDCounter getKDCounter() { return kdCounter; }
	@Override public LinkedList<Integer> getEffectIDs() { return effectIDs; }

	@Override public int getHealth() { return health; }
}
