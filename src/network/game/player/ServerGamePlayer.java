/*
	Alle Spieler des Servers sind von diesem Typ. Kommt nicht im Client vor.
*/

package network.game.player;

import java.net.InetAddress;
import java.util.LinkedList;

import entity.Entity;
import entity.entities.dynamic.mob.ExtendedMob;
import graphics.Animation;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.game.effect.Effect;
import misc.game.kill.KDCounter;
import misc.game.KeyManager;
import misc.game.PlayerStats;
import misc.game.Team;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import network.lobby.LobbyPlayer;
import network.game.packets.EventPacket;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import network.game.player.ClientGamePlayerFrameUpdate;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;

public class ServerGamePlayer extends ExtendedMob implements GamePlayer
{
	private InetAddress ip;
	private KeyManager keyManager = new KeyManager();

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
		// for testing:
		super(position, new StaticAnimation(ImageFile.PLAYER.getImageID())); // TODO do real stuff
		this.ip = lobbyPlayer.getIP();
		
		this.name = lobbyPlayer.getName();
		this.rank = lobbyPlayer.getRank();
		this.team = lobbyPlayer.getTeam();

		this.avatar = lobbyPlayer.getAvatar();
		this.skills = lobbyPlayer.getSkills();
		this.items = lobbyPlayer.getItems();
	}

	@Override public void tick()
	{
		super.tick();
		if (keyManager.isLeftPressed())
		{
			accelerate(-0.1f, 0);
		}
		if (keyManager.isRightPressed())
		{
			accelerate(0.1f, 0);
		}
		if (keyManager.isJumpPressed())
		{
			accelerate(0, -0.1f);
		}
		accelerate(0, 0.05f);
	}

	public void onCollide(Entity e)
	{
		super.onCollide(e);
	}

	public void handleEvent(EventPacket eventPacket)
	{
		Debug.warnIf(eventPacket == null, "ServerGamePlayer.handleEvent(): eventPacket == null");
		keyManager.handleEvent(eventPacket);
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

	@Override public MinimizedGamePlayer toMinimizedEntity()
	{
		return new MinimizedGamePlayer(getImageID(), getPosition(), getName(), getHealth());
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

	/*
		getHealth, getPosition, getImageID, getEffects, sind schon von Entity definiert und müssen nicht nochmal geschrieben werden
	*/
}
