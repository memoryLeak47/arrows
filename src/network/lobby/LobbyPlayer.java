package network.lobby;

import java.io.Serializable;
import java.net.InetAddress;

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
		// TODO
		lockPacket = new LockUserPacket(false);
		//avatarPacket = new AvatarUserPacket();
		teamPacket = new TeamUserPacket(Team.TEAM0);
		//skillPacket = new SkillUserPacket();
		//itemPacket = new ItemUserPacket();
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
			Debug.quit("LobbyPlayer.applyUserPacket got wrong packet");
		}
	}

	public InetAddress getIP() { return ip; }
	public String getName() { return loginPacket.getName(); }
	public int getRank() { return loginPacket.getRank(); }
	public boolean isLocked() { return lockPacket.isLocked(); }
	public Team getTeam() { return teamPacket.getTeam(); }
	public int getAvatarID() { return avatarPacket.getAvatarID(); }
	public int[] getSkillIDs() { return skillPacket.getSkillIDs(); }
	public int[] getItemIDs() { return itemPacket.getItemIDs(); }
}
