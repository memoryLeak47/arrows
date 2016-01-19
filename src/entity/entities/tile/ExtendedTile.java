package entity.entities.tile;

import java.awt.Color;

import effect.Effect;
import entity.Entity;
import entity.MinimizedEntity;
import entity.entities.tile.tiles.*;
import graphics.Animation;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import player.property.Team;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;


public abstract class ExtendedTile extends Entity
{
	public static final int STONE_COLORID = Integer.parseInt("000000", 16);
	public static final int VOID_COLORID = Integer.parseInt("ffffff", 16);
	public static final int LAVA_COLORID = Integer.parseInt("ffbb00", 16);

	public static final int SPAWN_TEAM0_COLORID = Team.TEAM0.getColorID();
	public static final int SPAWN_TEAM1_COLORID = Team.TEAM1.getColorID();
	public static final int SPAWN_TEAM2_COLORID = Team.TEAM2.getColorID();
	public static final int SPAWN_TEAM3_COLORID = Team.TEAM3.getColorID();
	public static final int SPAWN_TEAM4_COLORID = Team.TEAM4.getColorID();

	public ExtendedTile(GamePosition position, Animation animation)
	{
		super(position, animation);
	}

	public boolean isStatic() { return true; }
		// needed for static rendering.
		// should return false if tile may move or change image

	public boolean isObstacle() { return false; }

	public boolean isCollidingTiles() { return false; }
	public boolean isCollidingBullets() { return false; }
	public boolean isCollidingPlayers() { return false; }

	@Override public MinimizedEntity toMinimizedEntity()
	{
		return new MinimizedTile(getPosition(), getImageID());
	}

	@Override public void applyEffect(Effect e) {}

	public static ExtendedTile getByColorID(int colorID, float x, float y)
	{
		if (colorID == STONE_COLORID)
			return new StoneTile(new GamePosition(x, y));
		if (colorID == VOID_COLORID)
			return new VoidTile(new GamePosition(x, y));
		if (colorID == LAVA_COLORID)
			return new LavaTile(new GamePosition(x, y));
		if (colorID == SPAWN_TEAM0_COLORID)
			return new SpawnTeamTile(Team.TEAM0, new GamePosition(x, y));
		if (colorID == SPAWN_TEAM1_COLORID)
			return new SpawnTeamTile(Team.TEAM1, new GamePosition(x, y));
		if (colorID == SPAWN_TEAM2_COLORID)
			return new SpawnTeamTile(Team.TEAM2, new GamePosition(x, y));
		if (colorID == SPAWN_TEAM3_COLORID)
			return new SpawnTeamTile(Team.TEAM3, new GamePosition(x, y));
		if (colorID == SPAWN_TEAM4_COLORID)
			return new SpawnTeamTile(Team.TEAM4, new GamePosition(x, y));

		Debug.warn("ExtendedTile.getByColorID(" + colorID + "): returns null");
		return null;
	}

	public PixelPosition getGridPosition()
	{
		return new PixelPosition((int) getPosition().getX(), (int) getPosition().getY());
	}

	@Override public GameSize getSize() { return new GameSize(1, 1); }
}
