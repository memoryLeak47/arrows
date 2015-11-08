package network.lobby;

import java.io.Serializable;
import java.net.InetAddress;

import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;
import misc.game.Team;
import misc.Debug;
import network.lobby.packets.UserPacket;
import network.lobby.packets.user.*;

public class LobbyPlayer implements Serializable
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
		this.ip = lobbyPlayer.ip;
		loginPacket = new LoginUserPacket(lobbyPlayer.loginPacket);
		lockPacket = new LockUserPacket(lobbyPlayer.lockPacket);
		avatarPacket = new AvatarUserPacket(lobbyPlayer.avatarPacket);
		teamPacket = new TeamUserPacket(lobbyPlayer.teamPacket);
		skillPacket = new SkillUserPacket(lobbyPlayer.skillPacket);
		itemPacket = new ItemUserPacket(lobbyPlayer.itemPacket);
	}

	public void assign(LobbyPlayer lobbyPlayer)
	{
		this.ip = lobbyPlayer.ip;
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
		if (ip == null)
			Debug.warn("LobbyPlayer.getIP(): ip == null");
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
