package menu.menues;

import java.net.InetAddress;

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

public class ClientLobbyMenu extends LobbyMenu // menu of client when in lobby
{
	private LobbyPlayer localPlayer; // Verweiß auf den eigenen LobbyPlayer
	private InetAddress serverIP; // Speichert die IP adresse des Servers

	public ClientLobbyMenu(String serverIPString)
	{
		try
		{
			this.serverIP = InetAddress.getByName(serverIPString); // Speichert die Internet-Adresse vom Server; Wird von JoinServerMenu übergeben
		} catch (Exception e) { Debug.warn("ClientLobbyMenu not a valid ip address: " + serverIPString); }
	}

	// Wird ausgeführt von Main.networkDevice.receive()
	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet instanceof LobbyPlayersPacket) // Wenn es sich bei dem Packet um die Liste aller Player handelt, dann
		{
			if (getLocalPlayer() == null)
			{
				setPlayers(((LobbyPlayersPacket) packet).getPlayers()); // setzte die komplette Liste neu
				Debug.note("ClientLobbyMenu.handlePacket(): received LobbyPlayersPacket -> eigene players neu gesetzt", Debug.Tags.LOBBYMENUINFO);
				updatePlayerIcons();
			}
			else
			{
				int i = playerToID(getLocalPlayer(), getPlayers());
				setPlayers(((LobbyPlayersPacket) packet).getPlayers()); // setzte die komplette Liste neu
				localPlayer = getPlayers().get(i);
				if (localPlayer == null)
				{
					Debug.warn("ClientLobbyMenu.handlePacket(): localPlayer == null");
				}
				updatePlayerIcons();
			}
		}
		else if (packet instanceof MapPacket)
		{
			if (getPhase() == TEAM_PHASE)
			{
				// TODO apply
				unlockAll();
			}
			else
			{
				Debug.error("client> got mappacket out of teamphase");
			}
		}
		else if (packet instanceof UserPacketWithID) // Wenn es sich bei dem Packet um UserPacketWithID handelt, dann
		{
			UserPacket userPacket = ((UserPacketWithID) packet).getUserPacket(); // entpacken des UserPackets aus dem UserpacketWithID

			if (userPacket instanceof LockUserPacket) // wenn du ein lock-packet erhalten hast
			{
				if (isServerPlayer(getPlayer(packet)))
				{
					nextPhase();
				}
				else
				{
					getPlayer(packet).applyUserPacket(userPacket);
				}
			}
			else if (userPacket instanceof DisconnectUserPacket)
			{
				if (getPlayers() == null)
				{
					Debug.warn("ClientLobbyMenu.handlePacket(): getPlayers() == null");
				}
				if (getPlayer(packet) == null)
				{
					Debug.warn("ClientLobbyMenu.handlePacket(): getPlayer(packet) == null");
				}
				getPlayers().remove(getPlayer(packet));
				unlockAll();
				updatePlayerIcons();
			}
			else // falls nicht.
			{
				switch (getPhase())
				{
					case TEAM_PHASE: // Falls man in der Team Phase ist
						if (userPacket instanceof TeamUserPacket) // Wenn Spieler das Team wechselt
						{
							if (getPlayer(packet) == null)
							{
								Debug.warn("ClientLobbyMenu.handlePacket(): getPlayer(packet) == null (2)");
							}
							getPlayer(packet).applyUserPacket(userPacket); // setzte das Team des jeweilgen Spielers
							updatePlayerIcons();
							unlockAll();
						}
						else if (userPacket instanceof LoginUserPacket) // Wenn sich ein Spieler einloggt
						{
							LobbyPlayer player = new LobbyPlayer((LoginUserPacket) userPacket); // Neuen LobbyPlayer erstellen
							if (getPlayers().size() < 1)
							{
								Debug.warn("ClientLobbyMenu.handlePacket(): getPlayers().size() == " + getPlayers().size());
							}
							getPlayers().add(player); // Zur Liste der LobbyPlayer hinzufügen
							if (localPlayer == null) // Da das erste LoginUserPacket, das man bekommt, das eigene ist
							{
								localPlayer = player; // Diesen LobbyPlayer als eigenen abspeichern
							}
							unlockAll();
							updatePlayerIcons();
						}
						else
						{
							Debug.error("Client can't accept packet (" + packet + ") in team phase"); // Alle anderen Packete werden in dieser Phase nicht angenommen
						}
						break;
					case AVATAR_PHASE: // Wenn man sich in der AvatarPhase befindet
						if (userPacket instanceof AvatarUserPacket) // Falls ein Spieler seinen Avatar wechselt
						{
							if(getPlayer(packet) == null)
							{
								Debug.warn("ClientLobbyMenu.handlePacket(): getPlayer(packet) == null (3)");
							}
							getPlayer(packet).applyUserPacket(userPacket); // Des jeweiligen Spielers Avatar wird in den LobbyPlayern geändert
						}
						else
						{
							Debug.error("Client can't accept packet (" + packet + ") in avatar phase"); // Alle anderen Packete werden in dieser Phase nicht angenommen
						}
						break;
					case SKILL_PHASE: // Wenn man in der SkillPhase ist
						if (userPacket instanceof SkillUserPacket) // Wenn ein Spieler ein Skill wechselt
						{
							getPlayer(packet).applyUserPacket(userPacket); // In der LobbyPlayer Liste übernehmen
						}
						else
						{
							Debug.error("Client can't accept packet (" + packet + ") in skill phase"); // Alle anderen Packete werden in dieser Phase nicht angenommen
						}
						break;
					case ITEM_PHASE:
						if (userPacket instanceof ItemUserPacket) // Wenn ein Spieler ein Item wechselt
						{
							getPlayer(packet).applyUserPacket(userPacket); // In der LobbyPlayer Liste übernehmen
						}
						else
						{
							Debug.error("Client can't accept packet (" + packet + ") in item phase"); // Alle anderen Packete werden in dieser Phase nicht angenommen
						}
						break;
					default:
						Debug.error("ClientLobbyMenu.handlePacket(...): wrong phase (" + getPhase() + ")"); // Da ist was ganz komisch gelaufen; Ungültige Phase
						break;
				}
			}
		}
		else
		{
			Debug.error("Client received wrong packet (" + packet + ")"); // packets, die nicht vom Typ UserPacketWithID sind werden nicht angenommen
		}
	}

	// Wird ausgeführt, wenn ChoosePlayerPropertyMenu mit okButton geschlossen wird
	@Override public void sendPlayerPropertyUpdate()
	{
		if (getLocalPlayer() == null)
		{
			Debug.warn("ClientLobbyMenu.sendPlayerPropertyUpdate(): getLocalPlayer == null");
		}
		switch (getPhase())
		{
			case AVATAR_PHASE:
				sendToServer(getLocalPlayer().getAvatarPacket());
				break;
			case SKILL_PHASE:
				sendToServer(getLocalPlayer().getSkillPacket());
				break;
			case ITEM_PHASE:
				sendToServer(getLocalPlayer().getItemPacket());
				break;
			default:
				Debug.error("ClientLobbyMenu.sendPlayerPropertyUpdate(): wrong phase: " + getPhase());
		}
	}

	// Wird aufgerufen, wenn man auf die Map clickt
	@Override public void mapPressed()
	{
		// TODO: Map anzeigen
	}

	// Wird aufgerufen, wenn man den Lock-Button drückt
	@Override public void lockPressed()
	{
		if (isPlayerPropertiesChoosen())
		{
			if (getLocalPlayer() == null)
			{
				Debug.warn("ClientLobbyMenu.lockPressed(): getLocalPlayer() == null");
			}
			sendToServer(new LockUserPacket(!getLocalPlayer().isLocked())); // sendet an den Server, dass man den lock-button betätigt hat
		}
		else
		{
			Debug.note("ClientLobbyMenu.lockPressed: Kann noch nicht locken, da noch nicht alle PlayerProperties gewählt wurden", Debug.Tags.LOBBYMENUINFO);
		}
	}

	@Override public void disconnectPressed()
	{
		sendToServer(new DisconnectUserPacket());
		Main.getMenues().remove(Main.getMenues().getLast());
		Debug.note("ClientLobbyMenu.disconnectPressed: LobbyMenu beendet", Debug.Tags.LOBBYMENUINFO);
	}

	// Wird aufgerufen, wenn man sein Team wechselt
	@Override public void teamPressed(Team team)
	{
		if (getLocalPlayer() == null)
		{
			Debug.warn("ClientLobbyMenu.teamPressed(): getLocalPlayer() == null");
		}
		if (!getLocalPlayer().isLocked() && !getLocalPlayer().getTeam().equals(team))
		{
			sendToServer(new TeamUserPacket(team)); // An die anderen Spieler senden
		}
	}


	@Override public void avatarPressed(Avatar avatar)
	{
		// if new avatar TODO
		// sendToServer(new AvatarUserPacket(avatar)); // TODO
	}

	@Override public void skillPressed(Skill[] skills)
	{
		// if new skills TODO
		// sendToServer(new SkillUserPacket(skills));
	}

	@Override public void itemPressed(Item[] items)
	{
		// if new items TODO
		// sendToServer(new ItemUserPacket(items));
	}

	@Override public LobbyPlayer getLocalPlayer()
	{
		if (localPlayer == null)
		{
			Debug.warn("ClientLobbyMenu.getLocalPlayer(): getLocalPlayer return null");
		}
		return localPlayer;
	}

	// returnt den Spieler, der den das übergebene Packet anspricht
	private LobbyPlayer getPlayer(Packet packet)	
	{
		if (packet == null)
		{
			Debug.error("ClientLobbyMenu.getPlayer(): packet == null");
		}
		UserPacketWithID userPacketWithID = (UserPacketWithID) packet;
		return getPlayers().get(userPacketWithID.getID());
	}

	// Sendet das Packet zum Server
	private void sendToServer(Packet packet)
	{
		send(packet, serverIP);
	}

	private boolean isServerPlayer(LobbyPlayer player)
	{
		return player == getServerPlayer();
	}

	private LobbyPlayer getServerPlayer()
	{
		if (getPlayers() == null)
			Debug.warn("ClientLobbyMenu.getServerPlayer(): getPlayers() == null");
		if (getPlayers().get(0) == null)
		{
			Debug.warn("ClientLobbyMenu.getServerPlayer(): returns null");
		}
		return getPlayers().get(0);
	}
}
