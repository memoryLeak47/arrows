/*
	Wird vom Server zum Client in jedem Frame gesendet. 
	Speichert allgemein bekannte Daten vom Client. Die Daten der externen Player
*/

package player;

import misc.math.game.GamePosition;
import graphics.ImageID;

public class ClientGamePlayerFrameUpdate implements java.io.Serializable
{
	private int health;
	private GamePosition position;
	private ImageID imageID;

	public ClientGamePlayerFrameUpdate(int health, GamePosition position, ImageID imageID)
	{
		this.health = health;
		this.position = new GamePosition(position);
		this.imageID = new ImageID(imageID);
	}

	public int getHealth() { return health; }
	public GamePosition getPosition() { return position; }
	public ImageID getImageID() { return imageID; }
}
