package network.lobby;

import java.io.Serializable;
import java.net.InetAddress;

import game.avatar.Avatar;
import game.skill.Skill;
import game.item.Item;
import game.Team;
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
		loginPacket = new LoginUserPacket(lobbyPlayer.loginPacket);
		lockPacket = new LockUserPacket(lobbyPlayer.lockPacket);
		avatarPacket = new AvatarUserPacket(lobbyPlayer.avatarPacket);
		teamPacket = new TeamUserPacket(lobbyPlayer.teamPacket);
		skillPacket = new SkillUserPacket(lobbyPlayer.skillPacket);
		itemPacket = new ItemUserPacket(lobbyPlayer.itemPacket);
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

	public InetAddress getIP() { return ip; }
	public String getName() { return loginPacket.getName(); }
	public int getRank() { return loginPacket.getRank(); }
	public boolean isLocked() { return lockPacket.isLocked(); }
	public Team getTeam() { return teamPacket.getTeam(); }
	public Avatar getAvatar() { return avatarPacket.getAvatar(); }
	public Skill[] getSkills() { return skillPacket.getSkills(); }
	public Item[] getItems() { return itemPacket.getItems(); }
}
