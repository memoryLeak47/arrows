/*
	getLocalPlayer() == 'updated local player' (gleicher verweis!!)
*/

package menu.menues;

import java.io.File;
import java.net.InetAddress;
import java.util.LinkedList;

import core.Main;
import core.Screen;
import player.property.Team;
import player.property.avatar.Avatar;
import player.property.item.Item;
import player.property.skill.Skill;
import tilemap.LobbyTileMap;
import menu.components.*;
import misc.Debug;
import misc.math.pixel.PixelRect;
import network.Packet;
import player.LobbyPlayer;
import network.lobby.packets.user.*;
import network.lobby.packets.*;

public class ServerLobbyMenu extends LobbyMenu // lobby-menu für den server
{
	private LinkedList<LobbyPlayer> updatedPlayers;
	private EditField mapSelectEditField;
	private Button mapSelectButton;

	public ServerLobbyMenu()
	{
		// Map Select - EditField
		getComponents().add(mapSelectEditField = new EditField(this, new PixelRect(Screen.WIDTH-240, 250, 50, 20), "default"));

		// Map Select - Button
		getComponents().add(mapSelectButton = new Button(this, new PixelRect(Screen.WIDTH-180, 250, 50, 20), "Ok")
		{
			@Override public void onClick(int mouseButton)
			{
				if (isEnabled())
				{
					File path = new File("res/maps/" + mapSelectEditField.getText() + ".png");
					LobbyTileMap newMap = LobbyTileMap.getByFile(path);

					if (newMap == null)
					{
						Debug.warn("ServerLobbyMenu: mapSelectButton.onClick(): can't load '" + path.getAbsolutePath() + "'");
						return;
					}
					if (newMap.getInts() == null)
					{
						Debug.warn("ServerLobbyMenu: mapSelectButton.onClick(): newMap.getInts == null");
						return;
					}
					if (getMiniMap() == null)
					{
						Debug.warn("ServerLobbyMenu: mapSelectButton.onClick(): getMiniMap == null");
						return;
					}

					getMiniMap().applyMap(newMap.getInts());
					setLobbyTileMap(newMap);

					// sendet neue Map zu allen Clients
					sendToAllClients(new MapPacket(newMap.getInts()));
					unlockAll();
				}
			}
		});

		Debug.warnIf(Main.getName() == null, "ServerLobbyMenu.<init>(): Main.getName() == null");
		Debug.warnIf(getPlayers() == null, "ServerLobbyMenu.<init>(): getPlayers() == null");

		updatedPlayers = new LinkedList<LobbyPlayer>();
		getPlayers().add(new LobbyPlayer(new LoginUserPacket(Main.getName(), Main.getRank()))); // server fügt eigenen lobby-player hinzu
		getUpdatedPlayers().add(getPlayers().getLast());
		updatePlayerIcons();
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		Debug.warnIf(packet == null, "ServerLobbyMenu.handlePacket(null, ip)");
		Debug.warnIf(ip == null, "ServerLobbyMenu.handlePacket(packet, null)");

		if (packet instanceof LockUserPacket)
		{
			Debug.warnIf(ipToPlayer(ip, getPlayers()) == null, "ServerLobbyMenu.handlePacket(LockUserPacket): no player with that IP");
			ipToPlayer(ip, getPlayers()).applyUserPacket((UserPacket) packet);
			ipToPlayer(ip, getUpdatedPlayers()).applyUserPacket((UserPacket) packet);
			redirectUserPacket((UserPacket) packet, ip); // das erhaltene packet wird an alle clients weitergegeben
		}
		else if (packet instanceof DisconnectUserPacket)
		{
			Debug.warnIf(ipToPlayer(ip, getPlayers()) == null, "ServerLobbyMenu.handlePacket(DisconnectUserPacket): no player with that IP");
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
						Debug.warnIf(ipToPlayer(ip, getPlayers()) == null, "ServerLobbyMenu.handlePacket(TeamUserPacket): no player with that IP");

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
							Debug.warn("server already got player with ip " + ip.getHostName()); // error
						}
						else // falls der spieler wirklich neu ist
						{
							LobbyPlayer newPlayer = new LobbyPlayer((LoginUserPacket) packet, ip); // neuer spieler wird erstellt
							Debug.note("New Player \"" + newPlayer.getName() + "\" joined the game und ist happy :)");
							send(new LobbyPlayersPacket(getPlayers()), ip); // liste ohne den Neuen an den Neuen senden.
							if (getLobbyTileMap() != null)
								send(new MapPacket(getLobbyTileMap().getInts()), ip); // Die Map des neuen wird gesetzt
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
						Debug.warnIf(ipToPlayer(ip, getPlayers()) == null, "ServerLobbyMenu.handlePacket(AvatarUserPacket): no player with that IP");

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
						Debug.warnIf(ipToPlayer(ip, getPlayers()) == null, "ServerLobbyMenu.handlePacket(SkillUserPacket): no player with that IP");

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
						Debug.warnIf(ipToPlayer(ip, getPlayers()) == null, "ServerLobbyMenu.handlePacket(ItemUserPacket): no player with that IP");

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
				Debug.warn("ServerLobbyMenu.sendPlayerPropertyUpdate(): wrong phase: " + getPhase());
		}
	}

	@Override public void lockPressed()
	{
		if (lockButtonPressable())
		{
			sendUserPacketFromServer(new LockUserPacket(true));
			nextPhase();
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

	@Override public void tick()
	{
		super.tick();
		lockButton.setEnabled(lockButtonPressable());
	}

	// protected

	@Override protected void nextPhase()
	{
		super.nextPhase();
		Debug.note("ServerLobbyMenu.nextPhase(): now in phase (" + getPhase() + ")");
		updatePlayers();
		sendToAllClients(new LobbyPlayersPacket(getPlayers()));

		switch (getPhase()) // -1, da phase++ schon passiert ist
		{
			case TEAM_PHASE+1:
				mapSelectEditField.setEnabled(false);
				mapSelectButton.setEnabled(false);
				break;
			case GAME_PHASE:
				Debug.note("GAME START");
				Main.getMenues().add(new ServerGameInterface(getLobbyTileMap(), getPlayers()));
				break;
		}
	}

	@Override protected void unlockAll()
	{
		super.unlockAll();
		for (LobbyPlayer player : getUpdatedPlayers())
		{
			player.applyUserPacket(new LockUserPacket(false));
		}
	}


	// private

	private boolean allPlayersLocked()
	{
		Debug.warnIf(getPlayers().size() < 1, "ServerLobbyMenu(): getPlayers().size() = " + getPlayers().size());

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

	private void teamPressedWithID(int id, Team team)
	{
		Debug.warnIf(id < 0 || id > getUpdatedPlayers().size(), "ServerLobbyMenu.teamPressedWithID(): id (" + id + ") is out of range");
		Debug.warnIf(team == null, "ServerLobbyMenu.teamPressedWithID(): team == null");
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
		Debug.warnIf(id < 0 || id > getUpdatedPlayers().size(), "ServerLobbyMenu.redirectUserPacket(): id (" + id + ") is out of range");
		sendToAllClients(new UserPacketWithID(packet, id));
	}

	private void sendToAllClients(Packet packet)
	{
		Debug.warnIf(getPlayers().size() < 1, "ServerLobbyMenu.sendToAllClients(): getPlayers().size() = " + getPlayers().size());
		for (int i = 1; i < getPlayers().size(); i++) // für all client-spieler
		{
			send(packet, getPlayers().get(i).getIP()); // erhalte das packet!
		}
	}

	private void sendToTeam(Packet packet, Team team)
	{
		Debug.warnIf(team == null, "ServerLobbyMenu(): team == null");
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
		Debug.warnIf(updatedPlayers == null, "ServerLobbyMenu.getUpdatedPlayers(): updatedPlayers = null");
		Debug.warnIf(updatedPlayers.size() < 1, "ServerLobbyMenu.getUpdatedPlayers(): updatedPlayers.size() = " + updatedPlayers.size(), Debug.Tags.EXTENDED_WARNINGS);
		return updatedPlayers;
	}

	private boolean lockButtonPressable()
	{
		return (allPlayersLocked() && isLobbyTileMapSet() && arePlayerPropertiesChosen());
	}

	// Setzt die "Players" auf den Stand von updated Players
	private void updatePlayers()
	{
		Debug.warnIf(getUpdatedPlayers().size() < 1, "ServerLobbyMenu.updatePlayers(): getUpdatedPlayers().size() = " + getUpdatedPlayers().size());

		for (int i = 0; i < getUpdatedPlayers().size(); i++)
		{
			getPlayers().get(i).assign(getUpdatedPlayers().get(i));
			Debug.warnIf((getPlayers().get(i).getIP() == null) && (i != 0), "ServerLobbyMenu.updatePlayers(): getPlayers().get(" + i + ").getIP() == null");
		}
		Debug.note("ServerLobbyMenu.updatePlayers(): now getPlayers().size() = " + getPlayers().size());
	}

	// getter

	@Override public LobbyPlayer getLocalPlayer()
	{
		Debug.warnIf(getPlayers().size() < 1, "ServerLobbyMenu.getLocalPlayer(): getPlayers().size() = " + getPlayers().size());
		Debug.warnIf(getPlayers().get(0) == null, "ServerLobbyMenu.getLocalPlayer(): returns null");
		return getPlayers().get(0);
	}

	@Override public String getHeadline() { return "Server - LobbyMenu"; }
}
