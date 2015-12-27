/*
	Alle Spieler des Servers sind von diesem Typ. Kommt nicht im Client vor.
*/

package network.game.player;

import java.net.InetAddress;
import java.util.LinkedList;

import entity.entities.mob.Mob;
import graphics.Animation;
import graphics.animations.AnimationContainer;
import graphics.ImageID;
import misc.Debug;
import misc.game.effect.Effect;
import misc.game.kill.KDCounter;
import misc.game.PlayerStats;
import misc.game.Team;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import network.lobby.LobbyPlayer;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import network.game.player.ClientGamePlayerFrameUpdate;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;

public class ServerGamePlayer extends Mob implements GamePlayer
{
	private InetAddress ip;

	private String name;
	private int rank;

	private short[] charges;
	private PlayerStats playerStats;

	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private KDCounter kdCounter = new KDCounter();

	private Team team;
	private int health;
	private Animation animation;

	public ServerGamePlayer(LobbyPlayer lobbyPlayer, GamePosition position)
	{
		super(position, new GameSize(50, 50), new AnimationContainer()); // TODO do real stuff
		this.ip = lobbyPlayer.getIP();
		
		this.name = lobbyPlayer.getName();
		this.rank = lobbyPlayer.getRank();
		this.team = lobbyPlayer.getTeam();

		this.avatar = lobbyPlayer.getAvatar();
		this.skills = lobbyPlayer.getSkills();
		this.items = lobbyPlayer.getItems();

	}

	public LocalClientGamePlayerFrameUpdate toLocalClientGamePlayerFrameUpdate()
	{
		return new LocalClientGamePlayerFrameUpdate(Effect.toMinimizedEffects(getEffects()) , getPlayerStats(), getCharges());
	}

	public ClientGamePlayerFrameUpdate toClientGamePlayerFrameUpdate()
	{
		return new ClientGamePlayerFrameUpdate(getHealth(), getPosition(), getImageID());
	}

	private int calcMass()
	{
		int mass = getAvatar().getMassStat();
		for (int i = 0; i < getItems().length; i++)
		{
			mass += getItems()[i].getMassStat();
		}
		return mass;
	}

	// getter
	public InetAddress getIP() { return ip; }

	@Override public String getName() { return name; }
	public int getRank() { return rank; }

	public LinkedList<Effect> getEffects()
	{
		return null; // TODO
	}

	public short[] getCharges() { return charges; }
	@Override public LinkedList<Integer> getEffectIDs() { return Effect.toEffectIDs(getEffects()); }
	public PlayerStats getPlayerStats() { return playerStats; }

	public Avatar getAvatar() { return avatar; }
	public Skill[] getSkills() { return skills; }
	public Item[] getItems() { return items; }

	public KDCounter getKDCounter() { return kdCounter; }

	@Override public Team getTeam() { return team; }
	@Override public int getHealth() { return health; }
	@Override public ImageID getImageID() { return animation.getImageID(); }

	/*
		getHealth, getPosition, getImageID, getEffects, sind schon von Entity definiert und müssen nicht nochmal geschrieben werden
	*/
}
