/*
	Wird vom Server zum Client in jedem Frame gesendet. 
	Speichert allgemein bekannte Daten vom Client. Die Daten der externen Player
*/

package network.game.player;

import misc.math.Position;
import graphics.ImageID;

public class ClientGamePlayerFrameUpdate implements java.io.Serializable
{
	private int health;
	private Position position;
	private ImageID imageID;

	public ClientGamePlayerFrameUpdate(int health, Position position, ImageID imageID)
	{
		this.health = health;
		this.position = new Position(position);
		this.imageID = new ImageID(imageID);
	}

	public int getHealth() { return health; }
	public Position getPosition() { return position; }
	public ImageID getImageID() { return imageID; }
}
