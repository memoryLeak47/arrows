package player;

import java.awt.Color;

import core.Screen;
import entity.MinimizedEntity;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.compress.*;
import misc.math.Camera;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import misc.math.pixel.PixelPosition;
import player.property.Team;

public class MinimizedGamePlayer extends MinimizedEntity
{
	private float health;
	private float maxHealth;
	private String name;
	private Team team;

	public MinimizedGamePlayer(GamePosition position, ImageID imageID, String name, float health, float maxHealth, Team team, boolean[] effectIDs)
	{
		super(position, imageID, effectIDs);
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
		gamePos = gamePos.plusY(getSize().getY()/-2);
		PixelPosition pos = Camera.get().gamePositionToPixelPosition(gamePos);
		int length = (int) ((health / maxHealth)*50.f);
		Screen.g().fillRect((int) (pos.getX()-(float)length/2), pos.getY() - 20, length, 5);
	}

	public String getName() { return name; }
	public float getHealth() { return health; }
	public float getMaxHealth() { return maxHealth; }

	@SuppressWarnings("unchecked")
	public MinimizedGamePlayer(CompressBuffer buffer)
	{
		super(buffer);
		health = buffer.cutFloat();
		maxHealth = buffer.cutFloat();
		name = buffer.cutString();
		team = (Team) buffer.cutByCID(Compressor.TEAM_CID);
	}

	@Override public byte getCID() { return Compressor.MINIMIZED_GAME_PLAYER_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat(new byte[][]{
			super.compress(),
			Compressor.compressFloat(getHealth()),
			Compressor.compressFloat(getMaxHealth()),
			Compressor.compressString(getName()),
			team.compress()
		});
	}
}
