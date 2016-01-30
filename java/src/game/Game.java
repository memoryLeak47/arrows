package game;

import java.util.LinkedList;
import java.awt.image.BufferedImage;

import core.Main;
import entity.Entity;
import entity.MinimizedEntity;
import bullet.MinimizedBullet;
import cosmetic.ExtendedCosmetic;
import misc.Debug;
import misc.math.Camera;
import damage.Kill;
import player.ClientGamePlayer;
import player.GamePlayer;
import tile.map.GameTileMap;
import tile.map.LobbyTileMap;

public abstract class Game
{
	private Camera cam;
	private GameTileMap tileMap;
	private LinkedList<ExtendedCosmetic> cosmetics = new LinkedList<ExtendedCosmetic>();
	private LinkedList<Kill> kills = new LinkedList<Kill>();

	public Game(LobbyTileMap lobbyTileMap)
	{
		this.tileMap = new GameTileMap(lobbyTileMap);
		Main.setGame(this);
	}

	protected void initCamera()
	{
		cam = new Camera(getLocalPlayerID());
	}

	public abstract void tick();

	// getter
	protected abstract int getLocalPlayerID();

	// Returnt alle Player. Gebraucht für die MiniMap
	public abstract LinkedList<GamePlayer> getUncastedPlayers();

	public GamePlayer getLocalPlayer() { return getUncastedPlayers().get(getLocalPlayerID()); }

	public abstract LinkedList<MinimizedEntity> getMinimizedEntities();

	public LinkedList<ExtendedCosmetic> getCosmetics()
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

	public GameTileMap getGameTileMap()
	{
		Debug.warnIf(tileMap == null, "Game.getGameTileMap(): returns null");
		return tileMap;
	}

	public static Game get()
	{
		Debug.warnIf(Main.getGame() == null, "Game.get(): returns null");
		return Main.getGame();
	}

	public Camera getCamera() { return cam; }
}
