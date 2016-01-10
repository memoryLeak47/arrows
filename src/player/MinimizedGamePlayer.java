package player;

import java.awt.Color;

import core.Screen;
import entity.MinimizedEntity;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.Camera;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import misc.math.pixel.PixelPosition;
import player.property.Team;

public class MinimizedGamePlayer extends MinimizedEntity
{
	private int health;
	private int maxHealth;
	private String name;
	private Team team;

	public MinimizedGamePlayer(GamePosition position, ImageID imageID, String name, int health, int maxHealth, Team team /*, Effects TODO*/)
	{
		super(position, imageID);
		this.health = health;
		this.maxHealth = maxHealth;
		this.name = name;
		this.team = team;
	}

	@Override public void render()
	{
		super.render();
		Screen.g().setColor(team.getColor());
		GamePosition gamePos = new GamePosition(getPosition());
		gamePos.addY(getSize().getY()/-2);
		PixelPosition pos = Camera.get().gamePositionToPixelPosition(gamePos);
		int length = (int) ((float) health / (float) maxHealth)*50;
		Screen.g().fillRect((int) (pos.getX()-(float)length/2), pos.getY() - 20, length, 5);
	}

	public String getName() { return name; }
	public int getHealth() { return health; }
}
