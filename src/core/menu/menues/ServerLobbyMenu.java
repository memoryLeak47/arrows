package core.menu.menues;

import java.net.InetAddress;

import core.Main;
import game.Team;
import misc.Debug;
import network.Packet;
import network.lobby.LobbyPlayer;
import network.lobby.packets.user.*;
import network.lobby.packets.*;

public class ServerLobbyMenu extends LobbyMenu // lobby-menu für den server
{
	public ServerLobbyMenu()
	{
		getPlayers().add(new LobbyPlayer(new LoginUserPacket(Main.getName(), Main.getRank()))); // server fügt eigenen lobby-player hinzu
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
				else if (packet instanceof LoginUserPacket) // falls das packet ein LoginUserPacket ist
				{
					if (gotIP(ip)) // und er schon einer der spieler ist
					{
						Debug.quit("server already got player with ip " + ip.getHostName()); // error
					}
					else // falls der spieler wirklich neu ist
					{
						LobbyPlayer newPlayer = new LobbyPlayer((LoginUserPacket) packet, ip); // neuer spieler wird erstellt
						send(new LobbyPlayersPacket(getPlayers()), ip); // liste ohne den Neuen an den Neuen senden.
						getPlayers().add(newPlayer); // Neuen zur player liste hinzufügen
						// goto redirectUserPacket(packet);
					}
				}
				else // falls das packet iwas andres ist
				{
					Debug.quit("Server can't accept packet in team phase"); // error
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

	@Override public void teamPressed(Team team)
	{
		teamPressedWithID(0, team);
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

	private void teamPressedWithID(int id, Team team)
	{
		sendToAllClients(new UserPacketWithID(new TeamUserPacket(team), id));
	}

	private void sendUserPacketFromServer(UserPacket packet)
	{
		sendToAllClients(new UserPacketWithID(packet, 0));
	}

	private int ipToID(InetAddress ip)
	{
		for (int i = 1; i < getPlayers().size(); i++) // für alle clients
		{
			if (getPlayers().get(i).getIP().equals(ip)) // wenn eure ip die ip ist
			{
				return i; // returne deine ID
			}
		} // falls kein spieler gefunden wurde
		Debug.log("ServerLobbyMenu.ipToPlayerID(...): no LobbyPlayer with ip " + ip.getHostName()); // error
		return -1;
	}

	private LobbyPlayer ipToPlayer(InetAddress ip)
	{
		return getPlayers().get(ipToID(ip));
	}

	private void redirectUserPacket(UserPacket packet, InetAddress ip)
	{
		sendToAllClients(new UserPacketWithID(packet, ipToID(ip)));
	}

	private void sendToAllClients(Packet packet)
	{
		for (int i = 1; i < getPlayers().size(); i++) // für all client-spieler
		{
			send(packet, getPlayers().get(i).getIP()); // erhalte das packet!
		}
	}

	private boolean gotIP(InetAddress ip)
	{
		for (int i = 1; i < getPlayers().size(); i++) // für alle client-spieler
		{
			if (getPlayers().get(i).getIP().equals(ip)) // wenn dies deine IP ist
			{
				return true; // returne true
			}
		} // falls die ip neu ist
		return false; // returne false
	}

	@Override protected LobbyPlayer getLocalPlayer() { return getPlayers().get(0); }
}
