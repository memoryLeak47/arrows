/*
	getLocalPlayer() == 'updated local player' (gleicher verweis!!)
*/

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
		if (Main.getName() == null)
			Debug.warn("ServerLobbyMenu.<init>(): Main.getName() == null");
		if (getPlayers() == null)
			Debug.warn("ServerLobbyMenu.<init>(): getPlayers() == null");

		updatedPlayers = new LinkedList<LobbyPlayer>();
		getPlayers().add(new LobbyPlayer(new LoginUserPacket(Main.getName(), Main.getRank()))); // server fügt eigenen lobby-player hinzu
		getUpdatedPlayers().add(getPlayers().getLast());
		updatePlayerIcons();
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet == null)
			Debug.warn("ServerLobbyMenu.handlePacket(null, ip)");
		if (ip == null)
			Debug.warn("ServerLobbyMenu.handlePacket(packet, null)");

		if (packet instanceof LockUserPacket)
		{
			if (ipToPlayer(ip, getPlayers()) == null)
				Debug.error("ServerLobbyMenu.handlePacket(LockUserPacket): no player with that IP");
			ipToPlayer(ip, getPlayers()).applyUserPacket((UserPacket) packet);
			ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((UserPacket) packet);
			updateLockButton(); // setzt LockButton.enabled
			redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
		}
		else if (packet instanceof DisconnectUserPacket)
		{
			if (ipToPlayer(ip, getPlayers()) == null)
				Debug.error("ServerLobbyMenu.handlePacket(DisconnectUserPacket): no player with that IP");
			redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben, (leider auch dem der disconnected ist)
			getPlayers().remove(ipToID(ip, getPlayers()));
			getUpdatedPlayers().remove(ipToID(ip, getUpdatedPlayers()));
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
						if (ipToPlayer(ip, getPlayers()) == null)
							Debug.error("ServerLobbyMenu.handlePacket(TeamUserPacket): no player with that IP");

						if (ipToPlayer(ip, getPlayers()).isLocked())
						{
							Debug.note("locked player sent TeamUserPacket");
							return;
						}
						ipToPlayer(ip, getPlayers()).applyUserPacket((TeamUserPacket) packet); // setze das TeamUserPacket vom sender-player auf das erhaltene
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((TeamUserPacket) packet); // setze das TeamUserPacket vom sender-player auf das erhaltene
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
							getUpdatedPlayers().add(new LobbyPlayer(newPlayer));
							redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
							updatePlayerIcons();
							unlockAll();
						}
					}
					else // falls das packet iwas anderes ist
					{
						Debug.warn("Server can't accept packet (" + packet + ") in team phase"); // error
					}
					break;
				case AVATAR_PHASE: // falls wir in der avatar phase sind
					if (packet instanceof AvatarUserPacket) // und das packet ein AvatarUserPacket ist
					{
						if (ipToPlayer(ip, getPlayers()) == null)
							Debug.error("ServerLobbyMenu.handlePacket(AvatarUserPacket): no player with that IP");

						if (inMyTeam(ipToPlayer(ip, getUpdatedPlayers())))
						{
							ipToPlayer(ip, getPlayers()).applyUserPacket((AvatarUserPacket) packet); // setze das AvatarUserPacket vom sender-player auf das erhaltene
						}
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((AvatarUserPacket) packet); // setze das AvatarUserPacket vom sender-player auf das erhaltene
						sendToTeam(new UserPacketWithID((UserPacket) packet, ipToID(ip, getUpdatedPlayers())), ipToPlayer(ip, getUpdatedPlayers()).getTeam());
					}
					else
					{
						Debug.warn("Server can't accept packet (" + packet + ") in avatar-phase");
					}
					break;
				case SKILL_PHASE:
					if (packet instanceof SkillUserPacket) // und das packet ein SkillUserPacket ist
					{
						if (ipToPlayer(ip, getPlayers()) == null)
							Debug.error("ServerLobbyMenu.handlePacket(SkillUserPacket): no player with that IP");

						if (inMyTeam(ipToPlayer(ip, getPlayers())))
						{
							ipToPlayer(ip, getPlayers()).applyUserPacket((SkillUserPacket) packet);
						}
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((SkillUserPacket) packet);
						sendToTeam(new UserPacketWithID((UserPacket) packet, ipToID(ip, getPlayers())), ipToPlayer(ip, getUpdatedPlayers()).getTeam());
					}
					else
					{
						Debug.warn("Server can't accept packet (" + packet + ") in skill-phase");
					}
					break;
				case ITEM_PHASE:
					if (packet instanceof ItemUserPacket) // und das packet ein ItemUserPacket ist
					{
						if (ipToPlayer(ip, getPlayers()) == null)
							Debug.error("ServerLobbyMenu.handlePacket(ItemUserPacket): no player with that IP");

						if (inMyTeam(ipToPlayer(ip, getPlayers())))
						{
							ipToPlayer(ip, getPlayers()).applyUserPacket((ItemUserPacket) packet);
						}
						ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((ItemUserPacket) packet);
						sendToTeam(new UserPacketWithID((UserPacket) packet, ipToID(ip, getPlayers())), ipToPlayer(ip, getUpdatedPlayers()).getTeam());
					}
					else
					{
						Debug.warn("Server can't accept packet (" + packet + ") in item-phase");
					}
					break;
				default:
					Debug.warn("ServerLobbyMenu.handlePacket(...): wrong phase: " + getPhase());
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
		Debug.note("ServerLobbyMenu.nextPhase(): now in phase (" + getPhase() + ")");
		updatePlayers();
		sendToAllClients(new LobbyPlayersPacket(getPlayers()));

		switch (getPhase()) // -1, da phase++ schon passiert ist
		{
			case TEAM_PHASE+1:
				// TODO teamButtonDisable
				// TODO MapDisable
				break;
			case GAME_PHASE:
				Main.getMenues().add(new ServerGameInterface(getLobbyTileMap(), getPlayers()));
				break;
		}
	}

	private boolean allPlayersLocked()
	{
		if (getPlayers().size() < 1)
			Debug.warn("ServerLobbyMenu(): getPlayers().size() = " + getPlayers().size());

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
		if (id < 0 || id > getUpdatedPlayers().size())
			Debug.warn("ServerLobbyMenu.teamPressedWithID(): id (" + id + ") is out of range");
		if (team == null)
			Debug.warn("ServerLobbyMenu.teamPressedWithID(): team == null");
		TeamUserPacket packet;
		sendToAllClients(new UserPacketWithID(packet = new TeamUserPacket(team), id));
		getLocalPlayer().applyUserPacket(packet);
		updatePlayerIcons();
	}

	private void sendUserPacketFromServer(UserPacket packet)
	{
		sendToAllClients(new UserPacketWithID(packet, 0));
	}

	private void redirectUserPacket(UserPacket packet, InetAddress ip)
	{
		int id = ipToID(ip, getUpdatedPlayers());
		if (id < 0 || id > getUpdatedPlayers().size())
			Debug.warn("ServerLobbyMenu.redirectUserPacket(): id (" + id + ") is out of range");
		sendToAllClients(new UserPacketWithID(packet, id));
	}

	private void sendToAllClients(Packet packet)
	{
		if (getPlayers().size() < 1)
			Debug.warn("ServerLobbyMenu.sendToAllClients(): getPlayers().size() = " + getPlayers().size());
		for (int i = 1; i < getPlayers().size(); i++) // für all client-spieler
		{
			send(packet, getPlayers().get(i).getIP()); // erhalte das packet!
		}
	}

	private void sendToTeam(Packet packet, Team team)
	{
		if (team == null)
			Debug.warn("ServerLobbyMenu(): team == null");
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

	private LinkedList<LobbyPlayer> getUpdatedPlayers()
	{
		if (updatedPlayers == null)
			Debug.error("ServerLobbyMenu.getUpdatedPlayers(): updatedPlayers = null");
		if (updatedPlayers.size() < 1)
			Debug.warn("ServerLobbyMenu.getUpdatedPlayers(): updatedPlayers.size() = " + updatedPlayers.size());
		return updatedPlayers;
	}

	@Override protected void unlockAll()
	{
		super.unlockAll();
		for (LobbyPlayer player : getUpdatedPlayers())
		{
			player.applyUserPacket(new LockUserPacket(false));
		}
		updateLockButton(); // Setzt Button.enabled auf false
	}

	// Setzt die "Players" auf den Stand von updated Players
	private void updatePlayers()
	{
		if (getUpdatedPlayers().size() < 1)
			Debug.warn("ServerLobbyMenu.updatePlayers(): getUpdatedPlayers().size() = " + getUpdatedPlayers().size());

		for (int i = 0; i < getUpdatedPlayers().size(); i++)
		{
			getPlayers().get(i).assign(getUpdatedPlayers().get(i));
		}

		Debug.note("ServerLobbyMenu.updatePlayers(): now getPlayers().size() = " + getPlayers().size());
	}


	@Override public LobbyPlayer getLocalPlayer()
	{
		if (getPlayers().size() < 1)
			Debug.warn("ServerLobbyMenu.getLocalPlayer(): getPlayers().size() = " + getPlayers().size());
		if (getPlayers().get(0) == null)
			Debug.warn("ServerLobbyMenu.getLocalPlayer(): returns null");
		return getPlayers().get(0);
	}
}
