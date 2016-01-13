/*
	Wird vom Server zum Client in jedem Frame gesendet. 
	Speichert allgemein bekannte Daten vom Client. Die Daten der externen Player
*/

package player;

import misc.math.game.GamePosition;
import graphics.ImageID;

public class ClientGamePlayerFrameUpdate implements java.io.Serializable
{
	private float health;
	private float maxHealth;
	private GamePosition position;
	private ImageID imageID;

	public ClientGamePlayerFrameUpdate(float health, float maxHealth, GamePosition position, ImageID imageID)
	{
		this.health = health;
		this.maxHealth = maxHealth;
		this.position = new GamePosition(position);
		this.imageID = new ImageID(imageID);
	}

	public float getHealth() { return health; }
	public float getMaxHealth() { return maxHealth; }
	public GamePosition getPosition() { return position; }
	public ImageID getImageID() { return imageID; }
}
