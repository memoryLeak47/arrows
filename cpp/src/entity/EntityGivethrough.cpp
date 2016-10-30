#include "EntityGivethrough.hpp"

#include <misc/compress/CompressBuffer.hpp>

EntityGivethrough::EntityGivethrough(const GameVector& position_arg, const GameVector& size_arg, const GameVector& speed_arg, float rotation_arg, float spin_arg)
	: position(position_arg), size(size_arg), speed(speed_arg), rotation(rotation_arg), spin(spin_arg)
{}

EntityGivethrough::EntityGivethrough(CompressBuffer* buffer)
{
	GameVector* position_ = buffer->cutCompressable<GameVector>();
	GameVector* size_ = buffer->cutCompressable<GameVector>();
	GameVector* speed_ = buffer->cutCompressable<GameVector>();

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
	return ENTITY_GIVETHROUGH_CID;
}

std::string EntityGivethrough::getCompressString() const
{
	return position.getCompressString() + size.getCompressString() + speed.getCompressString() + compressFloat(rotation) + compressFloat(spin);
}
