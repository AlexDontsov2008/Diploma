#include "MoveableObject.hpp"

MoveableObject::MoveableObject()
: m_location(0, 0)
{}

Object::ObjectType MoveableObject::GetObjectType() const
{
    return MOVEABLE_OBJ;
}
