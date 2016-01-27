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
import tile.map.LobbyTileMap;

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
		if (controlsManager.isPlayerFocused())
		{
			Camera.get().centerPlayer();
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
		renderMap();
		renderEntities();
		renderSkills();
	}

	private final void renderMap()
	{
		PixelPosition tmp = Camera.get().gamePositionToPixelPosition(new GamePosition());
		PixelSize imageSize = new PixelSize(getUncastedGame().getMapImage().getWidth(), getUncastedGame().getMapImage().getHeight());
		int x = -tmp.getX();
		int y = -tmp.getY();
		int realX = Math.max(0, -x);
		int realY = Math.max(0, -y);
		int w = Math.min(imageSize.getX() - Math.max(0, x) - Math.max(0, imageSize.getX() - (x+Screen.WIDTH)), realX+imageSize.getX());
		int h = Math.min(imageSize.getY() - Math.max(0, y) - Math.max(0, imageSize.getY() - (y+Screen.HEIGHT)), realY+imageSize.getY());
		/* if (w <= 0 || h <= 0 || realX < 0 || realY < 0 || realX+w > imageSize.getX() || realY+h > imageSize.getY())
		{
			Debug.warn("GameInterface.renderMap(): outside of raster x: " + realX + ", y: " + realY + ", w: " + w + ", h: " + h);
		}
		*/
		BufferedImage subImage = getUncastedGame().getMapImage().getSubimage(Math.max(0, x), Math.max(0, y), w, h);
		Screen.g().drawImage(subImage, Math.max(0, -x), Math.max(0, -y), w, h, null);
	}

	private final void renderEntities()
	{
		for (MinimizedEntity entity : getUncastedGame().getMinimizedEntities())
		{
			entity.render();
		}
	}

	private final void renderSkills()
	{
		Skill[] skills = getUncastedGame().getLocalPlayer().getSkills();
		int iconSizeX = ImageFile.getImageByImageID(skills[0].getIconImageID()).getWidth();
		int iconSizeY = ImageFile.getImageByImageID(skills[0].getIconImageID()).getHeight()+1;

		int offsetX = iconSizeX/2;
		int offsetY = iconSizeY/2;

		int skillBoxX = Screen.WIDTH/2 - iconSizeX - offsetX;
		int skillBoxY = Screen.HEIGHT - iconSizeY * 5;
		int skillBoxW = (iconSizeX+offsetX) * 2 + offsetX;
		int skillBoxH = (iconSizeY+offsetY) * 2 + offsetY;


		Screen.g().setColor(new Color(50, 50, 50));
		Screen.g().fillRect(skillBoxX, skillBoxY, skillBoxW, skillBoxH);

		for (int i = 0; i < skills.length; i++)
		{
			int renderX = skillBoxX + offsetX + (iconSizeX + offsetX) * (i%2);
			int renderY;
			if (i > 1) // untere skills
			{
				renderY = skillBoxY + offsetY + iconSizeY + offsetY;
			}
			else // obere skills
			{
				renderY = skillBoxY + offsetY;
			}
			float fullness = getLocalPlayerCharges()[i]/Skill.MAX_CHARGE;

			if (fullness == 1)
				Screen.g().setColor(new Color(0, 255, 0, 100));
			else
				Screen.g().setColor(new Color(0, 0, 255, 100));

			Screen.g().drawImage(ImageFile.getImageByImageID(skills[i].getIconImageID()), renderX, renderY, null);
			Screen.g().fillRect(renderX, (int) (renderY+iconSizeY-fullness*iconSizeY), iconSizeX, (int) (iconSizeY*fullness));
		}
	}

	protected abstract float[] getLocalPlayerCharges();

	protected Game getUncastedGame() { return game; }

}
