/*
	Wird vom Server zum Client in jedem Frame gesendet. 
	Speichert allgemein bekannte Daten vom Client. Die Daten der externen Player
*/

package player;

import graphics.ImageID;
import misc.compress.*;
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

	@SuppressWarnings("unchecked")
	public ClientGamePlayerFrameUpdate(CompressBuffer buffer)
	{
		health = buffer.cutFloat();
		maxHealth = buffer.cutFloat();
		position = (GamePosition) buffer.cutByCID(Compressor.GAME_POSITION_CID);
		imageID = (ImageID) buffer.cutByCID(Compressor.IMAGE_ID_CID);
		effectIDs = buffer.cutBooleanArray();
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
