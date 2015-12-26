package core.game;

import java.util.LinkedList;
import java.awt.image.BufferedImage;

import core.Main;
import entity.Entity;
import entity.entities.bullet.MinimizedBullet;
import entity.entities.cosmetic.Cosmetic;
import misc.Debug;
import misc.game.Camera;
import misc.game.kill.Kill;
import network.game.player.ClientGamePlayer;
import network.game.player.GamePlayer;
import tilemap.GameTileMap;
import tilemap.LobbyTileMap;

public abstract class Game
{
	private Camera cam;
	private GameTileMap tileMap;
	private LinkedList<Cosmetic> cosmetics;
	private LinkedList<Kill> kills;

	public Game(LobbyTileMap lobbyTileMap)
	{
		this.tileMap = new GameTileMap(lobbyTileMap);
		Main.setGame(this);
	}

	abstract LinkedList<MinimizedBullet> getBullets();

	// Returnt alle Entities außer Tiles (Player, Bullets, Cosmetics)
	public LinkedList<Entity> getDynamicEntities()
	{
		Debug.warn("Game.getDynamicEntities(): return null TODO");
		return null;
	}

	// Returnt alle Player. Gebraucht für die MiniMap
	public abstract LinkedList<GamePlayer> getUncastedPlayers();


	// MiniMap Hintergrund
	public BufferedImage getPixelMapImage()
	{
		Debug.warn("Game.getPixelMapImage(): return null TODO");
		return null;
	}

	// returnt die GameTileMap als ein Bild, wie es im Spiel erscheint
	public BufferedImage getMapImage()
	{
		Debug.warn("Game.getMapImage(): return null TODO");
		return null;
	}

	protected GameTileMap getGameTileMap()
	{
		Debug.warnIf(tileMap == null, "Game.getGameTileMap(): returns null");
		return tileMap;
	}

	public Camera getCamera() { return cam; }
}
