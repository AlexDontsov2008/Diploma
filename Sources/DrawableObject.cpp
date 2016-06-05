#include "DrawableObject.hpp"


DrawableObject::DrawableObject()
{

}

DrawableObject::~DrawableObject()
{

}

Object::ObjectType DrawableObject::GetObjectType() const
{
    return Object::DRAWABLE_OBJ;
}
