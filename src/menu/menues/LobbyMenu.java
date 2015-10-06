package menu.menues;

import java.util.LinkedList;
import java.net.InetAddress;

import core.Main;
import core.Screen;
import menu.NetworkingMenu;
import menu.components.*;
import game.Team;
import game.avatar.Avatar;
import game.skill.Skill;
import game.item.Item;
import game.tilemap.LobbyTileMap;
import graphics.ImageFile;
import misc.Debug;
import misc.math.Rect;
import network.lobby.LobbyPlayer;
import network.lobby.packets.user.LockUserPacket;
import network.Packet;

public abstract class LobbyMenu extends NetworkingMenu
{
	public static final int TEAM_PHASE = 0;
	public static final int AVATAR_PHASE = 1;
	public static final int SKILL_PHASE = 2;
	public static final int ITEM_PHASE = 3;
	public static final int GAME_PHASE = 4;
 
	private int phase;
	private LobbyTileMap lobbyTileMap;
	protected Button lockButton; // Verweiß auf den NextStep/LockIn Button
	private LinkedList<LobbyPlayer> players; // Bluemi: protected -> private; added setter
	private TeamListPanel teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index

	public LobbyMenu()
	{
		phase = TEAM_PHASE;
		players = new LinkedList<LobbyPlayer>();

		// Top Label
		getComponents().add(new Label(this, new Rect(300, 10, 100, 20), "Lobby"));

		teamListPanel = new TeamListPanel(this, new Rect(100, 100, 600, 600));
		getComponents().add(teamListPanel);

		// lock Button
		lockButton = new Button(this, new Rect(Screen.WIDTH - 250, 600, 200, 60), getLockButtonCaption())
		{
			@Override public void onClick(int mouseButton)
			{
				lockPressed();
			}
		}; // Lock-Button
		getComponents().add(lockButton);

		getComponents().add(new Button(this, new Rect(1000, 100, 200, 140), "Map Placeholder")
		{
			@Override public void onClick(int mouseButton)
			{
				mapPressed();
			}
		}); // Map Placeholder
		getComponents().add(new Button(this, new Rect(20, 500, 20, 20), "Disconnect")
		{
			@Override public void onClick(int mouseButton)
			{
				disconnectPressed();	
			}
		});
	}

	// Wird von unterklassen aufgerufen, nachdem ein Spieler bearbeitet wurde
	protected final void updatePlayerIcons()
	{
		teamListPanel.update();
	}

	public abstract void handlePacket(Packet packet, InetAddress ip);
	public abstract void lockPressed();
	public abstract void teamPressed(Team team);
	public abstract void avatarPressed(Avatar avatar);
	public abstract void skillPressed(Skill[] skills);
	public abstract void itemPressed(Item[] items);
	public abstract void mapPressed();
	public abstract void disconnectPressed();
	public abstract void sendPlayerPropertyUpdate(); // wird ausgeführt, wenn das ChoosePlayerPropertyMenu mit dem Ok-Button geschlossen wird
	public abstract LobbyPlayer getLocalPlayer();

	public int getPhase() { return phase; }
	public LinkedList<LobbyPlayer> getPlayers()
	{
		if (players == null)
			Debug.warn("LobbyMenu.getPlayers() returns null");
		if (players.size() < 1)
			Debug.warn("LobbyMenu.getPlayers(): size() = " + players.size());
		return players;
	} // public damit TeamListPanel darauf zugreifen kann

	protected void setPlayers(LinkedList<LobbyPlayer> players) 
	{ 
		if (players == null)
			Debug.warn("LobbyMenu.setPlayers(null)");
		this.players = players; 
	}

	private String getLockButtonCaption()
	{
		if (this instanceof ClientLobbyMenu)
		{
			return "Ready";
		}
		else if (this instanceof ServerLobbyMenu)
		{
			return "Next Phase";
		}
		Debug.error("LobbyMenu.getLockButtonCaption: wrong lobby-menu-subclass");
		return null;
	}

	protected void nextPhase()
	{
		phase++;
		switch (getPhase())
		{
			case AVATAR_PHASE:
			{
				ImageFile.loadFromTo(ImageFile.ARCHER_ICON, ImageFile.ARCHER_ICON);
				break;	
			}
			// TODO load others
		}
		unlockAll();
	}

	protected void unlockAll()
	{
		for (LobbyPlayer player : getPlayers())
		{
			player.applyUserPacket(new LockUserPacket(false));
		}
	}

	protected boolean isPlayerPropertiesChoosen()
	{
		switch (phase)
		{
			case AVATAR_PHASE: return getLocalPlayer().isAvatarChoosen();
			case SKILL_PHASE: return getLocalPlayer().isSkillsChoosen();
			case ITEM_PHASE: return getLocalPlayer().isItemsChoosen();
		}

		return true; // In jeder anderen Phase gibt es keine PlayerProperties, die man wählen müsste, es sind also immer alle belegt
	}

	protected boolean inMyTeam(LobbyPlayer player)
	{
		if (player == null)
			Debug.warn("LobbyMenu.player == null");

		if (player.getTeam().equals(Team.TEAM0) || getLocalPlayer().getTeam().equals(Team.TEAM0))
		{
			return false;
		}
		return getLocalPlayer().getTeam().equals(player.getTeam());
	}

	protected int ipToID(InetAddress ip, LinkedList<LobbyPlayer> players)
	{
		if (ip == null)
			Debug.warn("LobbyMenu.ipToID(null, ...)");
		if (players == null)
			Debug.error("LobbyMenu.ipToID(): players == null");
		if (players.size() < 2)
			Debug.warn("LobbyMenu.ipToID(..., players): players.size = " + players.size());

		for (int i = 1; i < players.size(); i++) // für alle clients
		{
			if (players.get(i).getIP() == null)
				Debug.error("LobbyMenu.ipToID(): players.get(" + i + ").getIP() == null");
			if (players.get(i).getIP().equals(ip)) // wenn eure ip die ip ist
			{
				return i; // returne deine ID
			}
		} // falls kein spieler gefunden wurde
		Debug.warn("LobbyMenu.ipToID(...): no LobbyPlayer with ip (" + ip.getHostName() + ") returning -1"); // error
		return -1;
	}

	protected LobbyPlayer ipToPlayer(InetAddress ip, LinkedList<LobbyPlayer> players)
	{
		if (ip == null)
			Debug.warn("LobbyMenu.ipToPlayer(null, ...)");

		int id = ipToID(ip, players);
		if (id < 0 || id > players.size())
			Debug.error("LobbyMenu.ipToPlayer(" + ip.getHostName() + ", ...): id (" + id + ") out of range");
		return players.get(ipToID(ip, players));
	}

	protected boolean ipIn(InetAddress ip, LinkedList<LobbyPlayer> players)
	{
		for (int i = 1; i < players.size(); i++) // für alle client-spieler
		{
			if (players.get(i).getIP().equals(ip)) // wenn dies deine IP ist
			{
				return true; // returne true
			}
		} // falls die ip neu ist
		return false; // returne false
	}

	protected int playerToID(LobbyPlayer player, LinkedList<LobbyPlayer> players)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (players.get(i) == player)
			{
				return i;
			}
		}
		Debug.warn("LobbyMenu.playerToID(...): player to found");
		return 0;
	}

	protected LobbyTileMap getLobbyTileMap()
	{
		if (lobbyTileMap == null)
		{
			Debug.warn("LobbyMenu.getLobbyTileMap(): lobbyTileMap == null");
		}
		return lobbyTileMap;
	}
}
