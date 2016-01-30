package player;

import java.net.InetAddress;

import player.property.avatar.Avatar;
import player.property.skill.Skill;
import player.property.item.Item;
import player.property.Team;
import misc.Debug;
import misc.compress.*;
import network.lobby.packets.UserPacket;
import network.lobby.packets.user.*;

public class LobbyPlayer implements Compressable
{
	private InetAddress ip;

	private LoginUserPacket loginPacket;
	private LockUserPacket lockPacket;
	private AvatarUserPacket avatarPacket;
	private TeamUserPacket teamPacket;
	private SkillUserPacket skillPacket;
	private ItemUserPacket itemPacket;

	private LobbyPlayer()
	{
		lockPacket = new LockUserPacket(false);
		avatarPacket = new AvatarUserPacket((byte)-1); // -1 => no avatar
		teamPacket = new TeamUserPacket(Team.TEAM0);
		skillPacket = new SkillUserPacket(new byte[]{-1,-1,-1,-1});
		itemPacket = new ItemUserPacket(new byte[]{-1,-1,-1});
	}

	public LobbyPlayer(LoginUserPacket loginPacket, InetAddress ip)
	{
		this();
		Debug.warnIf(ip == null, "LobbyPlayer.<init>(LoginUserPacket, InetAddress): ip == null", Debug.Tags.EXTENDED_WARNINGS);

		this.loginPacket = loginPacket;
		this.ip = ip;
	}

	public LobbyPlayer(LoginUserPacket loginPacket)
	{
		this();
		this.loginPacket = loginPacket;
	}

	public LobbyPlayer(LobbyPlayer lobbyPlayer)
	{
		Debug.warnIf(ip == null, "LobbyPlayer.<init>(LobbyPlayer): ip == null", Debug.Tags.EXTENDED_WARNINGS);
		this.ip = lobbyPlayer.ip;
		loginPacket = new LoginUserPacket(lobbyPlayer.loginPacket);
		lockPacket = new LockUserPacket(lobbyPlayer.lockPacket);
		avatarPacket = new AvatarUserPacket(lobbyPlayer.avatarPacket);
		teamPacket = new TeamUserPacket(lobbyPlayer.teamPacket);
		skillPacket = new SkillUserPacket(lobbyPlayer.skillPacket);
		itemPacket = new ItemUserPacket(lobbyPlayer.itemPacket);
	}

	public LobbyPlayer(CompressBuffer buffer)
	{
		loginPacket = (LoginUserPacket) buffer.cutByCID(Compressor.LOGIN_USER_PACKET_CID);
		lockPacket = (LockUserPacket) buffer.cutByCID(Compressor.LOCK_USER_PACKET_CID);
		avatarPacket = (AvatarUserPacket) buffer.cutByCID(Compressor.AVATAR_USER_PACKET_CID);
		teamPacket = (TeamUserPacket) buffer.cutByCID(Compressor.TEAM_USER_PACKET_CID);
		skillPacket = (SkillUserPacket) buffer.cutByCID(Compressor.SKILL_USER_PACKET_CID);
		itemPacket = (ItemUserPacket) buffer.cutByCID(Compressor.ITEM_USER_PACKET_CID);
	}

	@Override public byte getCID() { return Compressor.LOBBY_PLAYER_CID; }
	@Override public byte[] compress()
	{
		byte[] login = loginPacket.compress();
		byte[] lock = lockPacket.compress();
		byte[] avatar = avatarPacket.compress();
		byte[] team = teamPacket.compress();
		byte[] skill = skillPacket.compress();
		byte[] item = itemPacket.compress();

		byte[] bytes = new byte[login.length + lock.length + avatar.length + team.length + skill.length + item.length];

		for (int i = 0; i < login.length; i++)
		{
			bytes[i] = login[i];
		}

		for (int i = 0; i < lock.length; i++)
		{
			bytes[i+login.length] = lock[i];
		}

		for (int i = 0; i < avatar.length; i++)
		{
			bytes[i + login.length + lock.length] = avatar[i];
		}

		for (int i = 0; i < team.length; i++)
		{
			bytes[i + login.length + lock.length + avatar.length] = team[i];
		}

		for (int i = 0; i < skill.length; i++)
		{
			bytes[i + login.length + lock.length + avatar.length + team.length] = skill[i];
		}

		for (int i = 0; i < item.length; i++)
		{
			bytes[i + login.length + lock.length + avatar.length + team.length + skill.length] = item[i];
		}

		return bytes;
	}

	public void assign(LobbyPlayer lobbyPlayer)
	{
		Debug.warnIf(lobbyPlayer == null, "LobbyPlayer.assign(): lobbyPlayer == null");
		Debug.warnIf(lobbyPlayer.getIP() == null, "LobbyPlayer.assign(): lobbyPlayer.getIP() == null", Debug.Tags.EXTENDED_WARNINGS);
		this.ip = lobbyPlayer.getIP();
		loginPacket.assign(lobbyPlayer.loginPacket);
		lockPacket.assign(lobbyPlayer.lockPacket);
		avatarPacket.assign(lobbyPlayer.avatarPacket);
		teamPacket.assign(lobbyPlayer.teamPacket);
		skillPacket.assign(lobbyPlayer.skillPacket);
		itemPacket.assign(lobbyPlayer.itemPacket);
	}

	public final void applyUserPacket(UserPacket packet)
	{
		if (packet instanceof LoginUserPacket)
		{
			loginPacket = new LoginUserPacket((LoginUserPacket) packet);
		}
		else if (packet instanceof LockUserPacket)
		{
			lockPacket = new LockUserPacket((LockUserPacket) packet);
		}
		else if (packet instanceof AvatarUserPacket)
		{
			avatarPacket = new AvatarUserPacket((AvatarUserPacket) packet);
		}
		else if (packet instanceof TeamUserPacket)
		{
			teamPacket = new TeamUserPacket((TeamUserPacket) packet);
		}
		else if (packet instanceof SkillUserPacket)
		{
			skillPacket = new SkillUserPacket((SkillUserPacket) packet);
		}
		else if (packet instanceof ItemUserPacket)
		{
			itemPacket = new ItemUserPacket((ItemUserPacket) packet);
		}
		else
		{
			Debug.error("LobbyPlayer.applyUserPacket got wrong packet");
		}
	}

	public AvatarUserPacket getAvatarPacket() { return avatarPacket; }
	public SkillUserPacket getSkillPacket() { return skillPacket; }
	public ItemUserPacket getItemPacket() { return itemPacket; }

	public boolean isAvatarChosen()
	{
		// Wenn das AvatarPacket noch nicht erstellt ist
		if (avatarPacket == null)
		{
			Debug.warn("LobbyPlayer.isAvatarChoosen(): avatarPacket == null"); // Warnung anzeigen. Das Packet muss immer erzeugt sein
			return false;
		}
		// Wenn noch kein Avatar ausgerwählt ist
		if (avatarPacket.getAvatar() == null)
		{
			return false; // zurückgeben, dass der Avatar noch nicht belegt wurde
		}
		return true; // Der Avatar wurde belegt
	}
	public boolean areSkillsChosen()
	{
		// Wenn das SkillPacket noch nicht erstellt ist
		if (skillPacket == null)
		{
			Debug.warn("LobbyPlayer.isSkillChoosen(): skillPacket == null"); // Warnung anzeigen. Das Packet muss immer erzeugt sein
			return false; // zurückgeben, dass nicht alle Skills belegt wurden
		}
		// Wenn ein Skill noch nicht belegt ist
		for (int i = 0; i < skillPacket.getSkills().length; i++)
		{
			if (skillPacket.getSkills()[i] == null)
			{
				return false; // zurückgeben, dass nicht alle Skills belegt wurden
			}
		}
		return true; // Alle Skills wurden belegt
	}
	public boolean areItemsChosen()
	{
		// Wenn das ItemPacket noch nicht erstellt ist
		if (itemPacket == null)
		{
			Debug.warn("LobbyPlayer.isItemsChoosen(): itemPacket == null"); // Warnung anzeigen. Das Packet muss immer erzeugt sein
			return false; // zurückgeben, dass nicht alle Items belegt wurden
		}
		// Wenn ein Item noch nicht belegt ist
		for (int i = 0; i < itemPacket.getItems().length; i++)
		{
			if (itemPacket.getItems()[i] == null)
			{
				return false; // zurückgeben, dass nicht alle Items belegt wurden
			}
		}
		return true; // Alle Items wurden belegt
	}
	
	public InetAddress getIP()
	{
		Debug.warnIf(ip == null, "LobbyPlayer.getIP(): ip == null", Debug.Tags.EXTENDED_WARNINGS);
		return ip;
	}
	public String getName() { return loginPacket.getName(); }
	public int getRank() { return loginPacket.getRank(); }
	public boolean isLocked() { return lockPacket.isLocked(); }
	public Team getTeam() { return teamPacket.getTeam(); }
	public Avatar getAvatar() { return avatarPacket.getAvatar(); }
	public Skill[] getSkills() { return skillPacket.getSkills(); }
	public Item[] getItems() { return itemPacket.getItems(); }
}
