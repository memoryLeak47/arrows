package network;

import java.net.InetAddress;

import network.packets.lobby.*;

public class PlayerInfo
{
	private InetAddress ip;

	private UserLobbyPacket user; // Name + Rank
	private AvatarLobbyPacket avatar; // ID des gewählten Avatars
	private TeamLobbyPacket team;
	private LockLobbyPacket lock;

	public InetAddress getIP() { return ip; }
	public String getName() { return user.getName(); }
	public int getRank() { return user.getRank(); }
	// more getters
}
