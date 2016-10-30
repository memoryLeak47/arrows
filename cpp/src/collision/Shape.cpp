#include "Shape.hpp"

Shape::Shape(Entity* entity_arg)
	: entity(entity_arg)
{}

Shape::Shape(CompressBuffer*)
{}

std::string Shape::getCompressString() const
{
	return "";
}
