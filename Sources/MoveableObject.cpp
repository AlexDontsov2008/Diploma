#include "MoveableObject.hpp"

MoveableObject::MoveableObject()
: m_locations(sf::Vector2u(0, 0), sf::Vector2u(0, 0))
{}

Object::ObjectType MoveableObject::GetObjectType() const
{
    return MOVEABLE_OBJ;
}
