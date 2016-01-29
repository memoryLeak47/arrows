#ifndef __VECTOR_CLASS__
#define __VECTOR_CLASS__

class Vector
{
	private:
		float x, y;
	public:
		Vector(const Vector&);
		Vector(float, float);
		float getX() const;
		float getY() const;

		bool operator==(const Vector&) const;
		bool operator!=(const Vector&) const;
		const Vector& operator+(const Vector&) const;
		const Vector& operator-(const Vector&) const;
};

#endif
