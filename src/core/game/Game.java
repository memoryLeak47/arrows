package core.game;

import java.util.LinkedList;
import java.awt.image.BufferedImage;

import core.Main;
import entity.Entity;
import entity.MinimizedEntity;
import entity.entities.dynamic.spinnable.bullet.MinimizedBullet;
import entity.entities.dynamic.spinnable.cosmetic.ExtendedCosmetic;
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
	private LinkedList<ExtendedCosmetic> cosmetics = new LinkedList<ExtendedCosmetic>();
	private LinkedList<Kill> kills = new LinkedList<Kill>();

	public Game(LobbyTileMap lobbyTileMap)
	{
		this.tileMap = new GameTileMap(lobbyTileMap);
		Main.setGame(this);
	}

	public abstract void tick();

	// Getter

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
		Debug.warnIf(Game.get() == null, "Game.get(): returns null");
		return Main.getGame();
	}

	public Camera getCamera() { return cam; }
}
