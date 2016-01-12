package menu.menues;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.util.LinkedList;

import static core.Main.TILESIZE;
import core.Main;
import core.Screen;
import entity.MinimizedEntity;
import game.Game;
import graphics.ImageFile;
import menu.NetworkingMenu;
import menu.event.Event;
import misc.Debug;
import misc.math.Camera;
import misc.math.game.GamePosition;
import misc.math.pixel.PixelPosition;
import misc.math.pixel.PixelSize;
import player.LobbyPlayer;
import player.controls.PlayerControlsManager;
import player.property.skill.Skill;
import network.Packet;
import network.game.packets.PlayerControlsUpdatePacket;
import tilemap.LobbyTileMap;

public abstract class GameInterface extends NetworkingMenu
{
	private Game game;
	private PlayerControlsManager controlsManager = new PlayerControlsManager();

	public GameInterface(Game game)
	{
		setGame(game);
	}

	@Override public void tick()
	{
		super.tick();
		if (getUncastedGame() != null)
		{
			getUncastedGame().tick();
		}
		else
		{
			Debug.warn("GameInterface.tick(): getUncastedGame() == null");
		}
	}

	protected PlayerControlsUpdatePacket getPlayerControlsUpdatePacket()
	{
		return controlsManager.getPacketAndApply();
	}

	@Override public void onEvent(Event event)
	{
		controlsManager.onEvent(event);
	}

	private void setGame(Game game)
	{
		Debug.warnIf(game == null, "GameInterface.setGame(null)");
		this.game = game;
	}

	@Override public void render()
	{
		PixelPosition tmp = Camera.get().gamePositionToPixelPosition(new GamePosition());
		PixelSize imageSize = new PixelSize(getUncastedGame().getMapImage().getWidth(), getUncastedGame().getMapImage().getHeight());
		int x = -tmp.getX();
		int y = -tmp.getY();
		int w = imageSize.getX() - Math.max(0, x) - Math.max(0, imageSize.getX() - (x+Screen.WIDTH));
		int h = imageSize.getY() - Math.max(0, y) - Math.max(0, imageSize.getY() - (y+Screen.HEIGHT));
		BufferedImage subImage = getUncastedGame().getMapImage().getSubimage(Math.max(0, x), Math.max(0, y), w, h);
		Screen.g().drawImage(subImage, Math.max(0, -x), Math.max(0, -y), w, h, null);
		for (MinimizedEntity entity : getUncastedGame().getMinimizedEntities())
		{
			entity.render();
		}
		renderSkills();
	}

	private final void renderSkills()
	{
		Skill[] skills = getUncastedGame().getLocalPlayer().getSkills();
		int iconSizeX = ImageFile.getImageByImageID(skills[0].getIconImageID()).getWidth();
		int iconSizeY = ImageFile.getImageByImageID(skills[0].getIconImageID()).getHeight()+1;

		Screen.g().setColor(new Color(0, 0, 255, 100));
		for (int i = 0; i < skills.length; i++)
		{
			int renderX = (iconSizeX+20)*(i+1);
			int renderY = iconSizeY;
			Screen.g().drawImage(
				ImageFile.getImageByImageID(skills[i].getIconImageID()), renderX, renderY, null);
			float fullness = getLocalPlayerCharges()[i]/Skill.MAX_CHARGE;
			Screen.g().fillRect(renderX, (int) (renderY+iconSizeY-fullness*iconSizeY), iconSizeX, (int) (iconSizeY*fullness));
		}
	}

	protected abstract float[] getLocalPlayerCharges();

	protected Game getUncastedGame() { return game; }

}
