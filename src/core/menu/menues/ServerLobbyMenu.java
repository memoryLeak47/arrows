package core.menu.menues;

import java.net.InetAddress;

import core.Main;
import misc.Debug;
import network.Packet;
import network.lobby.LobbyPlayer;
import network.lobby.packets.user.*;
import network.lobby.packets.*;

public class ServerLobbyMenu extends LobbyMenu // lobby menu for the server
{
	public ServerLobbyMenu()
	{
		players.add(new LobbyPlayer(new LoginUserPacket(Main.getName(), Main.getRank()))); // server adds itself
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		switch (getPhase())
		{
			case TEAM_PHASE: // falls wir in der team/map phase sind
				if (packet instanceof TeamUserPacket) // und das packet ein TeamUserPacket ist
				{
					ipToPlayer(ip).applyUserPacket((TeamUserPacket) packet); // setze das TeamUserPacket vom sender-player auf das erhaltene
					// goto redirectUserPacket(packet);
				}
				else if (packet instanceof LoginUserPacket)
				{
					if (gotIP(ip))
					{
						Debug.quit("server already got player with ip " + ip.getHostName());
					}
					else
					{
						LobbyPlayer newPlayer = new LobbyPlayer((LoginUserPacket) packet, ip); // neuer spieler wird erstellt
						send(new LobbyPlayersPacket(players), ip); // liste ohne neuen an die ip des neuen senden.
						players.add(newPlayer); // zur player liste hinzufügen
						// goto redirectUserPacket(packet);
					}
				}
				else
				{
					Debug.quit("Server can't accept packet in team phase");
				}
				break;
			case AVATAR_PHASE: // falls wir in der avatar phase sind
				if (packet instanceof AvatarUserPacket) // und das packet ein AvatarUserPacket ist
				{
					ipToPlayer(ip).applyUserPacket((AvatarUserPacket) packet); // setze das AvatarUserPacket vom sender-player auf das erhaltene
					// goto redirectUserPacket(packet);
				}
				else
				{
					Debug.quit("Server can't accept packet in avatar phase");
				}
				break;
			case ATTRIBUTE_PHASE:
				if (packet instanceof AttributeUserPacket) // und das packet ein AttributeUserPacket ist
				{
					ipToPlayer(ip).applyUserPacket((AttributeUserPacket) packet); // setze das AttributeUserPacket vom sender-player auf das erhaltene
					// goto redirectUserPacket(packet);
				}
				else
				{
					Debug.quit("Server can't accept packet in attribute phase");
				}
				break;
			default:
				Debug.quit("ServerLobbyMenu.handlePacket(...): wrong phase");
				break;
		}
		redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
	}

	@Override public void mapPressed()
	{
		// TODO
	}

	@Override public void teamPressed(int team)
	{
		teamPressedWithID(team, 0);
	}

	@Override public void lockPressed()
	{
		sendUserPacketFromServer(new LockUserPacket(true));
		nextPhase();
	}

	@Override public void nextPhase()
	{
		// TODO
	}

	private void teamPressedWithID(int id, int team)
	{
		sendToAllClients(new UserPacketWithID(new TeamUserPacket(team), id));
	}

	private void sendUserPacketFromServer(UserPacket packet)
	{
		sendToAllClients(new UserPacketWithID(packet, 0));
	}

	private int ipToID(InetAddress ip)
	{
		for (int i = 1; i < players.size(); i++)
		{
			if (players.get(i).getIP().equals(ip))
			{
				return i;
			}
		}
		Debug.log("ServerLobbyMenu.ipToPlayerID(...): no LobbyPlayer with ip " + ip.getHostName());
		return -1;
	}


	private LobbyPlayer ipToPlayer(InetAddress ip)
	{
		return players.get(ipToID(ip));
	}

	private void redirectUserPacket(UserPacket packet, InetAddress ip)
	{
		sendToAllClients(new UserPacketWithID(packet, ipToID(ip)));
	}

	private void sendToAllClients(Packet packet)
	{
		for (int i = 1; i < players.size(); i++) // für all client spieler
		{
			send(packet, players.get(i).getIP()); // erhalte das packet!
		}
	}

	private boolean gotIP(InetAddress ip)
	{
		for (int i = 1; i < players.size(); i++)
		{
			if (players.get(i).getIP().equals(ip))
			{
				return true;
			}
		}
		return false;
	}

	@Override protected LobbyPlayer getLocalPlayer() { return players.get(0); }
}
