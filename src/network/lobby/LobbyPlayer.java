package network.lobby;

import java.net.InetAddress;

import network.lobby.packets.UserPacket;
import network.lobby.packets.user.*;
import misc.Debug;

public class LobbyPlayer
{
	private InetAddress ip;

	private LoginUserPacket loginPacket;
	private LockUserPacket lockPacket;
	private AvatarUserPacket avatarPacket;
	private TeamUserPacket teamPacket;
	private AttributeUserPacket attributePacket;

	public LobbyPlayer(LoginUserPacket loginPacket, InetAddress ip)
	{
		this.loginPacket = loginPacket;
		this.ip = ip;
	}

	public LobbyPlayer(LoginUserPacket loginPacket)
	{
		this.loginPacket = loginPacket;
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
		else if (packet instanceof AttributeUserPacket)
		{
			attributePacket = new AttributeUserPacket((AttributeUserPacket) packet);
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
	public int getTeam() { return teamPacket.getTeam(); }
	public int getAvatarID() { return avatarPacket.getAvatarID(); }
	public int[] getSkillIDs() { return attributePacket.getSkillIDs(); }
	public int[] getItemIDs() { return attributePacket.getItemIDs(); }
}
