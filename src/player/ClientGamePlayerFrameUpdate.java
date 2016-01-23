/*
	Wird vom Server zum Client in jedem Frame gesendet. 
	Speichert allgemein bekannte Daten vom Client. Die Daten der externen Player
*/

package player;

import graphics.ImageID;
import misc.compress.Compressable;
import misc.compress.Compressor;
import misc.math.game.GamePosition;

public class ClientGamePlayerFrameUpdate implements Compressable
{
	private float health;
	private float maxHealth;
	private GamePosition position;
	private ImageID imageID;
	private boolean[] effectIDs;

	public ClientGamePlayerFrameUpdate(float health, float maxHealth, GamePosition position, ImageID imageID, boolean[] effectIDs)
	{
		this.health = health;
		this.maxHealth = maxHealth;
		this.position = new GamePosition(position);
		this.imageID = new ImageID(imageID);
		this.effectIDs = effectIDs;
	}

	public float getHealth() { return health; }
	public float getMaxHealth() { return maxHealth; }
	public GamePosition getPosition() { return position; }
	public ImageID getImageID() { return imageID; }
	public boolean[] getEffectIDs() { return effectIDs; }

	@Override public byte getCID() { return Compressor.CLIENT_GAME_PLAYER_FRAME_UPDATE_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat(new byte[][]{
			Compressor.compressFloat(getHealth()),
			Compressor.compressFloat(getMaxHealth()),
			getPosition().compress(),
			getImageID().compress(),
			Compressor.compressBooleanArray(getEffectIDs())
		});
	}
}
