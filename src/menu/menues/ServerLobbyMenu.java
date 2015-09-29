package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import core.Main;
import game.Team;
import game.avatar.Avatar;
import game.skill.Skill;
import game.item.Item;
import misc.Debug;
import network.Packet;
import network.lobby.LobbyPlayer;
import network.lobby.packets.user.*;
import network.lobby.packets.*;

public class ServerLobbyMenu extends LobbyMenu // lobby-menu für den server
{
	private LinkedList<LobbyPlayer> updatedPlayers;

	public ServerLobbyMenu()
	{
		updatedPlayers = new LinkedList<LobbyPlayer>();
		getPlayers().add(new LobbyPlayer(new LoginUserPacket(Main.getName(), Main.getRank()))); // server fügt eigenen lobby-player hinzu
		updatePlayerIcons();
	}

	private void createUpdatedPlayers()
	{
		getUpdatedPlayers().clear();
		for (LobbyPlayer player : getPlayers())
		{
			getUpdatedPlayers().add(player);
		}
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet instanceof LockUserPacket)
		{
			ipToPlayer(ip, getPlayers()).applyUserPacket((UserPacket) packet);
			updateLockButton(); // setzt LockButton.enabled
			redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
		}
		else if (packet instanceof DisconnectUserPacket)
		{
			redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben, (leider auch dem der disconnected ist)
			removePlayer(ipToPlayer(ip, getPlayers()));
			unlockAll();
			updatePlayerIcons();
		}
		else
		{
			switch (getPhase())
			{
				case TEAM_PHASE: // falls wir in der team/map phase sind
					if (packet instanceof TeamUserPacket) // und das packet ein TeamUserPacket ist
					{
						if (ipToPlayer(ip, getPlayers()).isLocked())
						{
							Debug.note("locked player sent TeamUserPacket");
							return;
						}
						ipToPlayer(ip, getPlayers()).applyUserPacket((TeamUserPacket) packet); // setze das TeamUserPacket vom sender-player auf das erhaltene
						redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
						updatePlayerIcons();
						unlockAll();
					}
					else if (packet instanceof LoginUserPacket) // falls das packet ein LoginUserPacket ist
					{
						if (ipIn(ip, getPlayers())) // und er schon einer der spieler ist
						{
							Debug.error("server already got player with ip " + ip.getHostName()); // error
						}
						else // falls der spieler wirklich neu ist
						{
							LobbyPlayer newPlayer = new LobbyPlayer((LoginUserPacket) packet, ip); // neuer spieler wird erstellt
							send(new LobbyPlayersPacket(getPlayers()), ip); // liste ohne den Neuen an den Neuen senden.
							getPlayers().add(newPlayer); // Neuen zur player liste hinzufügen
							redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
							updatePlayerIcons();
							unlockAll();
						}
					}
					else // falls das packet iwas anderes ist
					{
						Debug.error("Server can't accept packet (" + packet + ") in team phase"); // error
					}
					break;
				case AVATAR_PHASE: // falls wir in der avatar phase sind
					if (packet instanceof AvatarUserPacket) // und das packet ein AvatarUserPacket ist
					{
						if (inMyTeam(ipToPlayer(ip, getPlayers())))
						{
							ipToPlayer(ip, getPlayers()).applyUserPacket((AvatarUserPacket) packet); // setze das AvatarUserPacket vom sender-player auf das erhaltene
						}
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((AvatarUserPacket) packet); // setze das AvatarUserPacket vom sender-player auf das erhaltene
						sendToTeam(packet, ipToPlayer(ip, getUpdatedPlayers()).getTeam());
					}
					else
					{
						Debug.error("Server can't accept packet (" + packet + ") in avatar-phase");
					}
					break;
				case SKILL_PHASE:
					if (packet instanceof SkillUserPacket) // und das packet ein AttributeUserPacket ist
					{
						if (inMyTeam(ipToPlayer(ip, getPlayers())))
						{
							ipToPlayer(ip, getPlayers()).applyUserPacket((SkillUserPacket) packet);
						}
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((SkillUserPacket) packet);
						sendToTeam(packet, ipToPlayer(ip, getUpdatedPlayers()).getTeam());
					}
					else
					{
						Debug.error("Server can't accept packet (" + packet + ") in skill-phase");
					}
					break;
				case ITEM_PHASE:
					if (packet instanceof ItemUserPacket) // und das packet ein ItemUserPacket ist
					{
						if (inMyTeam(ipToPlayer(ip, getPlayers())))
						{
							ipToPlayer(ip, getPlayers()).applyUserPacket((ItemUserPacket) packet);
						}
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((ItemUserPacket) packet);
						sendToTeam(packet, ipToPlayer(ip, getUpdatedPlayers()).getTeam());
					}
					else
					{
						Debug.error("Server can't accept packet (" + packet + ") in item-phase");
					}
					break;
				default:
					Debug.error("ServerLobbyMenu.handlePacket(...): wrong phase: " + getPhase());
					break;
			}
		}
	}

	// Wird ausgeführt, wenn ChoosePlayerPropertyMenu mit okButton geschlossen wird
	@Override public void sendPlayerPropertyUpdate()
	{
		switch (getPhase())
		{
			case AVATAR_PHASE:
				sendToTeam(new UserPacketWithID(getLocalPlayer().getAvatarPacket(), 0), getLocalPlayer().getTeam());
				break;
			case SKILL_PHASE:
				sendToTeam(new UserPacketWithID(getLocalPlayer().getSkillPacket(), 0), getLocalPlayer().getTeam());
				break;
			case ITEM_PHASE:
				sendToTeam(new UserPacketWithID(getLocalPlayer().getItemPacket(), 0), getLocalPlayer().getTeam());
				break;
			default:
				Debug.error("ServerLobbyMenu.sendPlayerPropertyUpdate(): wrong phase: " + getPhase());
		}
	}

	@Override public void mapPressed()
	{
		// TODO
	}

	@Override public void lockPressed()
	{
		// Wenn alle Client-Spieler gelockt sind
		if (allPlayersLocked())
		{
			// Wenn man seine PlayerProperties gewählt hat
			if (isPlayerPropertiesChoosen())
			{
				sendUserPacketFromServer(new LockUserPacket(true));
				nextPhase();
			}
		}
	}

	@Override public void teamPressed(Team team)
	{
		teamPressedWithID(0, team);
	}


	@Override public void disconnectPressed()
	{
		sendUserPacketFromServer(new DisconnectUserPacket());
		Main.getMenues().remove(Main.getMenues().getLast());
	}

	@Override public void avatarPressed(Avatar avatar) {}
	@Override public void skillPressed(Skill[] skills) {}
	@Override public void itemPressed(Item[] items) {}

	@Override protected void nextPhase()
	{
		super.nextPhase();
		switch (getPhase()-1) // -1, da phase++ schon passiert ist
		{
			case TEAM_PHASE:
			{
				// TODO teamButtonDisable
				// TODO MapDisable
				createUpdatedPlayers();
			}
			break;
		}
	}

	private boolean allPlayersLocked()
	{
		boolean enable = true;
		for (int i = 1; i < getPlayers().size(); i++) // i = 1 -> für alle Client-Spieler
		{
			if (!getPlayers().get(i).isLocked()) // Falls ein Spieler nicht gelockt ist:
			{
				enable = false; // den Button disablen
			}
		}
		return enable;	
	}

	// Prüft, ob der LockButton enabled ist oder nicht
	private void updateLockButton()
	{
		lockButton.setEnabled(allPlayersLocked());
	}

	private void teamPressedWithID(int id, Team team)
	{
		TeamUserPacket packet;
		sendToAllClients(new UserPacketWithID(packet = new TeamUserPacket(team), id));
		getLocalPlayer().applyUserPacket(packet);
		updatePlayerIcons();
	}

	private void sendUserPacketFromServer(UserPacket packet)
	{
		sendToAllClients(new UserPacketWithID(packet, 0));
	}

	private int ipToID(InetAddress ip, LinkedList<LobbyPlayer> players)
	{
		for (int i = 1; i < players.size(); i++) // für alle clients
		{
			if (players.get(i).getIP().equals(ip)) // wenn eure ip die ip ist
			{
				return i; // returne deine ID
			}
		} // falls kein spieler gefunden wurde
		Debug.note("ServerLobbyMenu.ipToPlayerID(...): no LobbyPlayer with ip " + ip.getHostName()); // error
		return -1;
	}

	private LobbyPlayer ipToPlayer(InetAddress ip, LinkedList<LobbyPlayer> players)
	{
		return players.get(ipToID(ip, getPlayers()));
	}

	private void redirectUserPacket(UserPacket packet, InetAddress ip)
	{
		sendToAllClients(new UserPacketWithID(packet, ipToID(ip, getPlayers())));
	}

	private void sendToAllClients(Packet packet)
	{
		for (int i = 1; i < getPlayers().size(); i++) // für all client-spieler
		{
			send(packet, getPlayers().get(i).getIP()); // erhalte das packet!
		}
	}

	private void sendToTeam(Packet packet, Team team)
	{
		if (team.equals(Team.TEAM0))
		{
			return;
		}

		for (int i = 1; i < getPlayers().size(); i++) // für all client-spieler
		{
			if (getPlayers().get(i).getTeam().equals(team))
			{
				send(packet, getPlayers().get(i).getIP()); // erhalte das packet!
			}
		}
	}

	private boolean ipIn(InetAddress ip, LinkedList<LobbyPlayer> player)
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

	private LinkedList<LobbyPlayer> getUpdatedPlayers() { return updatedPlayers; }

	@Override protected void unlockAll()
	{
		super.unlockAll();
		for (LobbyPlayer player : getUpdatedPlayers())
		{
			player.applyUserPacket(new LockUserPacket(false));
		}
		updateLockButton(); // Setzt Button.enabled auf false
	}

	@Override protected void removePlayer(LobbyPlayer player)
	{
		super.removePlayer(player);
		if (getUpdatedPlayers().contains(player))
		{
			getUpdatedPlayers().remove(player);
		}
	}

	private boolean inMyTeam(LobbyPlayer player)
	{
		if (player.getTeam().equals(Team.TEAM0) || getLocalPlayer().getTeam().equals(Team.TEAM0))
		{
			return false;
		}
		return getLocalPlayer().getTeam().equals(player.getTeam());
	}

	private void updatePlayers()
	{
		getPlayers().clear();
		for (LobbyPlayer player : getUpdatedPlayers())
		{
			getPlayers().add(player);
		}
	}

	@Override public LobbyPlayer getLocalPlayer() { return getPlayers().get(0); }
}
