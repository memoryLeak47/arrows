package entity.entities.tile;

import java.awt.Color;

import entity.Entity;
import entity.entities.tile.tiles.*;
import graphics.ImageFile;
import graphics.ImageID;
import misc.game.Team;
import misc.Debug;

public abstract class Tile extends Entity
{
	public static final int STONE_COLORID = Integer.parseInt("000000", 16);
	public static final int VOID_COLORID = Integer.parseInt("ffffff", 16);

	public static final int SPAWN_TEAM0_COLORID = Team.TEAM0.getColorID();
	public static final int SPAWN_TEAM1_COLORID = Team.TEAM1.getColorID();
	public static final int SPAWN_TEAM2_COLORID = Team.TEAM2.getColorID();
	public static final int SPAWN_TEAM3_COLORID = Team.TEAM3.getColorID();
	public static final int SPAWN_TEAM4_COLORID = Team.TEAM4.getColorID();

	public boolean isStatic() { return true; }
		// needed for static rendering.
		// should return false if tile may move or change image

	public static Tile getByColorID(int colorID)
	{
		if (colorID == STONE_COLORID)
			return new StoneTile();
		if (colorID == VOID_COLORID)
			return new VoidTile();
		if (colorID == SPAWN_TEAM0_COLORID)
			return new SpawnTeamTile(Team.TEAM0);
		if (colorID == SPAWN_TEAM1_COLORID)
			return new SpawnTeamTile(Team.TEAM1);
		if (colorID == SPAWN_TEAM2_COLORID)
			return new SpawnTeamTile(Team.TEAM2);
		if (colorID == SPAWN_TEAM3_COLORID)
			return new SpawnTeamTile(Team.TEAM3);
		if (colorID == SPAWN_TEAM4_COLORID)
			return new SpawnTeamTile(Team.TEAM4);

		Debug.warn("Tile.getByColorID(" + colorID + "): returns null");
		return null;
	}

	public ImageID getImageID()
	{
		Debug.warn("Tile.getImageID() returns null");
		return null; // TODO
	}
}
