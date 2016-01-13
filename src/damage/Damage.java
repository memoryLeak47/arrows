package damage;

import effect.Effect;

public class Damage
{
	private float hit, cut, magic;

	public Damage(float hit, float cut, float magic)
	{
		this.hit = hit;
		this.cut = cut;
		this.magic = magic;
	}

	public float getHit() { return hit; }
	public float getCut() { return cut; }
	public float getMagic() { return magic; }
}
