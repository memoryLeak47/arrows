#include "EntityGivethrough.hpp"

#include <misc/compress/CompressBuffer.hpp>
#include <collision/Shape.hpp>

EntityGivethrough::EntityGivethrough(Shape* shape_arg, const GameVector& position_arg, const GameVector& size_arg, const GameVector& speed_arg, float rotation_arg, float spin_arg)
	: shape(shape_arg), position(position_arg), size(size_arg), speed(speed_arg), rotation(rotation_arg), spin(spin_arg)
{}

EntityGivethrough::EntityGivethrough(CompressBuffer* buffer)
{
	if ((shape = buffer->cutCompressable<Shape>()) == nullptr)
	{
		Debug::error("EntityGivethrough::EntityGivethrough(buffer); could not cut Shape");
	}

	GameVector* position_ = (GameVector*) buffer->cutByCompressID(CompressIDs::GAME_VECTOR);
	GameVector* size_ = (GameVector*) buffer->cutByCompressID(CompressIDs::GAME_VECTOR);
	GameVector* speed_ = (GameVector*) buffer->cutByCompressID(CompressIDs::GAME_VECTOR);

	position = *position_;
	size = *size_;
	speed = *speed_;

	delete position_;
	delete size_;
	delete speed_;

	rotation = buffer->cutFloat();
	spin = buffer->cutFloat();
}

CompressID EntityGivethrough::getCompressID() const
{
	return CompressIDs::ENTITY_GIVETHROUGH;
}

std::string EntityGivethrough::getCompressString() const
{
	return shape->compress() + position.getCompressString() + size.getCompressString() + speed.getCompressString() + compressFloat(rotation) + compressFloat(spin);
}
