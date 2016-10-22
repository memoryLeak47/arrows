#ifndef __GAMEVECTOR_CLASS__
#define __GAMEVECTOR_CLASS__

class CompressBuffer;
class GameRect;

#include <misc/compress/Compressable.hpp>
#include <misc/compress/Cid.hpp>
#include <string>

class GameVector : public Compressable
{
	public:
		GameVector();
		GameVector(float x, float y);
		GameVector(CompressBuffer*);

		CID getCID() const override;
		std::string getCompressString() const override;
		bool inRect(const GameRect&) const;
		float getMagnitude() const;
		void setMagnitude(float mag);
		GameVector withMagnitude(float mag) const;
		GameVector getNormalized() const;
		GameVector getProjectionOn(const GameVector&) const;
		GameVector getOrthogonal() const;
		bool isValid() const;
		static float getScalarProduct(const GameVector& vec1, const GameVector& vec2);

		bool operator==(const GameVector&) const;
		bool operator!=(const GameVector&) const;
		GameVector operator+=(const GameVector&);
		GameVector operator-=(const GameVector&);
		GameVector operator+(const GameVector&) const;
		GameVector operator-(const GameVector&) const;
		GameVector operator-() const;
		GameVector operator*(float) const;
		GameVector operator/(float) const;
		std::string toString() const;
		float x, y;
};

#endif
