package core.game;

import java.util.LinkedList;
import java.awt.image.BufferedImage;

import core.Main;
import entity.Entity;
import entity.MinimizedEntity;
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
	private Camera cam = new Camera(getLocalPlayerID());
	private GameTileMap tileMap;
	private LinkedList<Cosmetic> cosmetics = new LinkedList<Cosmetic>();
	private LinkedList<Kill> kills = new LinkedList<Kill>();

	public Game(LobbyTileMap lobbyTileMap)
	{
		this.tileMap = new GameTileMap(lobbyTileMap);
		Main.setGame(this);
	}

	// Getter

	protected abstract int getLocalPlayerID();

	// Returnt alle Player. Gebraucht für die MiniMap
	public abstract LinkedList<GamePlayer> getUncastedPlayers();

	public abstract LinkedList<MinimizedEntity> getMinimizedEntities();

	public LinkedList<Cosmetic> getCosmetics()
	{
		Debug.warnIf(cosmetics == null, "Game.getCosmetics(): cosmetics == null");
		return cosmetics;
	}

	// MiniMap Hintergrund
	public BufferedImage getPixelMapImage()
	{
		Debug.warn("Game.getPixelMapImage(): return null TODO");
		return null;
	}

	// returnt die GameTileMap als ein Bild, wie es im Spiel erscheint

	public BufferedImage getMapImage()
	{
		Debug.warnIf(getGameTileMap().getStaticImage() == null, "Game.getMapImage(): returns null");
		return getGameTileMap().getStaticImage();
	}

	protected GameTileMap getGameTileMap()
	{
		Debug.warnIf(tileMap == null, "Game.getGameTileMap(): returns null");
		return tileMap;
	}

	public Camera getCamera() { return cam; }
}
