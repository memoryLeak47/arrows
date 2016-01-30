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

	public Damage(Damage damage)
	{
		this.hit = damage.hit;
		this.cut = damage.cut;
		this.magic = damage.magic;
	}

	public Damage times(Damage damage)
	{
		return new Damage(getHit() * damage.getHit(),
				  getCut() * damage.getCut(),
				  getMagic() * damage.getMagic());
	}

	public Damage plus(Damage damage)
	{
		return new Damage(getHit() + damage.getHit(),
				  getCut() + damage.getCut(),
				  getMagic() + damage.getMagic());
	}

	public float getHit() { return hit; }
	public float getCut() { return cut; }
	public float getMagic() { return magic; }
}
