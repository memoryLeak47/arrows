/*
	Alle Spieler des Servers sind von diesem Typ. Kommt nicht im Client vor.
*/

package player;

import java.net.InetAddress;
import java.util.LinkedList;

import static core.Main.STANDART_ACCELERATION;
import damage.Damage;
import entity.Entity;
import entity.entities.dynamic.mob.ExtendedMob;
import graphics.Animation;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import graphics.ImageID;
import effect.Effect;
import damage.KDCounter;
import player.PlayerStats;
import player.property.Team;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import menu.event.Event;
import network.game.packets.PlayerControlsUpdatePacket;
import player.LobbyPlayer;
import player.controls.PlayerControls;
import player.ClientGamePlayerFrameUpdate;
import player.LocalClientGamePlayerFrameUpdate;
import player.property.avatar.Avatar;
import player.property.skill.Skill;
import player.property.item.Item;

public abstract class ServerGamePlayer extends ExtendedMob implements GamePlayer
{
	private InetAddress ip;
	private PlayerControls controls = new PlayerControls();

	private String name;
	private int rank;

	private PlayerStats playerStats;

	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private KDCounter kdCounter = new KDCounter();

	private Team team;
	private Animation animation;

	protected ServerGamePlayer(LobbyPlayer lobbyPlayer, GamePosition position, Animation animation)
	{
		// for testing:
		super(position, animation); // TODO do real stuff

		Debug.warnIf(lobbyPlayer == null, "ServerGamePlayer.<init>(): lobbyPlayer == null");
		Debug.warnIf(lobbyPlayer.getIP() == null, "ServerGamePlayer.<init>(): lobbyPlayer.getIP() == null", Debug.Tags.EXTENDED_WARNINGS);
		Debug.warnIf(lobbyPlayer.getAvatar() == null, "ServerGamePlayer.<init>(): lobbyPlayer.getAvatar() == null");
		Debug.warnIf(lobbyPlayer.getSkills() == null, "ServerGamePlayer.<init>(): lobbyPlayer.getSkills() == null");
		Debug.warnIf(lobbyPlayer.getItems() == null, "ServerGamePlayer.<init>(): lobbyPlayer.getItems() == null");

		this.ip = lobbyPlayer.getIP();

		this.name = lobbyPlayer.getName();
		this.rank = lobbyPlayer.getRank();
		this.team = lobbyPlayer.getTeam();

		this.avatar = lobbyPlayer.getAvatar();
		this.skills = lobbyPlayer.getSkills();
		this.items = lobbyPlayer.getItems();

		for (int i = 0; i < skills.length; i++)
		{
			skills[i].setPlayer(this);
		}

		resetHealth();
	}

	@Override public void tick()
	{
		super.tick();
		for (byte i = 0; i < Skill.SKILLS_SIZE; i++)
		{
			getSkills()[i].tick();
		}
		applyKeys();
	}

	private void applyKeys()
	{
		if (controls.isLeft())
		{
			accelerate(-STANDART_ACCELERATION, 0);
		}
		if (controls.isRight())
		{
			accelerate(STANDART_ACCELERATION, 0);
		}
		if (controls.isJump())
		{
			jump();
		}
	}

	public void onCollide(Entity e)
	{
		super.onCollide(e);
	}

	@Override protected void applyDamage(Damage damage)
	{
		damage((int) ((float) damage.getHit() / (float) getResistanceStat().getHit()));
		damage((int) ((float) damage.getCut() / (float) getResistanceStat().getCut()));
		damage((int) ((float) damage.getMagic() / (float) getResistanceStat().getMagic()));
	}

	public void applyPlayerControlsUpdatePacket(PlayerControlsUpdatePacket packet)
	{
		Debug.warnIf(packet == null, "ServerGamePlayer.applyPlayerControlsUpdatePacket(): packet == null");
		controls.applyPlayerControlsUpdatePacket(packet);
		for (int i = 0; i < packet.controls.length; i++)
		{
			if (packet.controls[i] >= 100)
			{
				if ((packet.controls[i]-100) < Skill.SKILLS_SIZE)
				{
					getSkills()[packet.controls[i]-100].onKeyPressed();
				}
			}
			else
			{
				if ((packet.controls[i]) < Skill.SKILLS_SIZE)
				{
					getSkills()[packet.controls[i]].onKeyReleased();
				}
			}
		}
	}

	public LocalClientGamePlayerFrameUpdate toLocalClientGamePlayerFrameUpdate()
	{
		return new LocalClientGamePlayerFrameUpdate(Effect.toMinimizedEffects(getEffects()) , getPlayerStats(), getCharges());
	}

	public ClientGamePlayerFrameUpdate toClientGamePlayerFrameUpdate()
	{
		return new ClientGamePlayerFrameUpdate(getHealth(), getMaxHealth(), getPosition(), getImageID());
	}

	@Override public MinimizedGamePlayer toMinimizedEntity()
	{
		return new MinimizedGamePlayer(getPosition(), getImageID(), getName(), getHealth(), getMaxHealth(), getTeam());
	}

	// getter
	public InetAddress getIP() { return ip; }

	@Override public String getName() { return name; }
	public int getRank() { return rank; }

	// for sub
	public abstract int getMassStat();
	public abstract int getMaxHealthStat();
	public abstract int getRegenerationStat();
	public abstract int getAccelerationStat();
	public abstract Damage getDamageStat();
	public abstract Damage getResistanceStat();
	public abstract String getAvatarName();


	public float[] getCharges()
	{
		float[] s = new float[Skill.SKILLS_SIZE];
		for (byte i = 0; i < Skill.SKILLS_SIZE; i++)
		{
			s[i] = getSkills()[i].getCharge();
		}
		return s;
	}

	@Override public int getMaxHealth()
	{
		int health = getMaxHealthStat();
		if (getItems() == null)
			return health;
		for (int i = 0; i < getItems().length; i++)
		{
			health += getItems()[i].getHealthStat();
		}
		return health;
	}

	public int getMass()
	{
		int mass = getMassStat();
		for (int i = 0; i < getItems().length; i++)
		{
			mass += getItems()[i].getMassStat();
		}
		return mass;
	}

	public Damage getDamage()
	{
		return getDamageStat();
	}



	@Override public LinkedList<Integer> getEffectIDs() { return Effect.toEffectIDs(getEffects()); }
	public PlayerStats getPlayerStats() { return playerStats; }

	public Avatar getAvatar()
	{
		Debug.warnIf(avatar == null, "ServerGamePlayer.getAvatar(): avatar == null");
		return avatar;
	}

	@Override public Skill[] getSkills()
	{
		Debug.warnIf(skills == null, "ServerGamePlayer.getSkills(): skills == null");
		return skills;
	}

	public Item[] getItems()
	{
		Debug.warnIf(items == null, "ServerGamePlayer.getItems(): items == null");
		return items;
	}

	public KDCounter getKDCounter() { return kdCounter; }

	@Override public Team getTeam() { return team; }

	public GamePosition getMousePosition() { return new GamePosition(controls.mousePosition); }

	/*
		getHealth, getPosition, getImageID, getEffects, sind schon von Entity definiert und müssen nicht nochmal geschrieben werden
	*/
}
