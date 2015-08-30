package core.menu.menues;

import java.net.InetAddress;

import misc.Debug;
import network.Packet;
import network.lobby.LobbyPlayer;
import network.lobby.packets.user.*;
import network.lobby.packets.*;

public class ClientLobbyMenu extends LobbyMenu // menu of client when in lobby
{
	private LobbyPlayer localPlayer;
	private InetAddress serverIP;

	public ClientLobbyMenu(String serverIPString)
	{
		try
		{
			this.serverIP = InetAddress.getByName(serverIPString);
		} catch (Exception e) { Debug.log("ClientLobbyMenu not a valid ip address"); }
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		// Wenn es sich bei dem Packet um die Liste aller Player handelt, dann
		if (packet instanceof LobbyPlayersPacket)
		{
			localPlayer = null;
			setPlayers(((LobbyPlayersPacket) packet).getPlayers()); // setzte die komplette Liste neu
			return;
		}
		else if (packet instanceof UserPacketWithID) // Wenn es sich bei dem Packet um UserPacketWithID handelt, dann
		{
			UserPacket userPacket = ((UserPacketWithID) packet).getUserPacket();

			switch (getPhase())
			{
				// Falls man in der Team Phase ist
				case TEAM_PHASE:
					if (userPacket instanceof TeamUserPacket)
					{
						getPlayer(packet).applyUserPacket(userPacket);
					}
					else if (userPacket instanceof LoginUserPacket)
					{
						LobbyPlayer player = new LobbyPlayer((LoginUserPacket) userPacket);
						getPlayers().add(player);
						if (localPlayer == null)
						{
							localPlayer = player;
						}
					}
					else
					{
						Debug.quit("Client can't accept packet in team phase");
					}
					break;
				case AVATAR_PHASE:
					if (userPacket instanceof AvatarUserPacket)
					{
						getPlayer(packet).applyUserPacket(userPacket);
					}
					else
					{
						Debug.quit("Client can't accept packet in avatar phase");
					}
					break;
				case ATTRIBUTE_PHASE:
					if (userPacket instanceof AttributeUserPacket)
					{
						getPlayer(packet).applyUserPacket(userPacket);
					}
					else
					{
						Debug.quit("Client can't accept packet in attribute phase");
					}
					break;
				default:
					Debug.quit("ClientLobbyMenu.handlePacket(...): wrong phase");
					break;
			}
		}
		else
		{
			Debug.quit("Client received wrong packet");
		}
	}

	@Override public void mapPressed()
	{
		// TODO
	}

	@Override public void teamPressed(int team)
	{
		sendToServer(new TeamUserPacket(team));
	}

	@Override public void lockPressed()
	{
		sendToServer(new LockUserPacket(!getLocalPlayer().isLocked()));
	}

	@Override public void nextPhase()
	{
		// TODO
	}

	@Override protected LobbyPlayer getLocalPlayer() { return localPlayer; }

	private LobbyPlayer getPlayer(Packet packet) // converts a UserPacketWithID to a player
	{
		UserPacketWithID userPacketWithID = (UserPacketWithID) packet;
		return getPlayers().get(userPacketWithID.getID());
	}

	private void sendToServer(Packet packet)
	{
		send(packet, serverIP);
	}
}
