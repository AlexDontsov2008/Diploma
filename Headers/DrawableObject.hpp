#ifndef _DRAWABLEOBJECT_HPP_
#define _DRAWABLEOBJECT_HPP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Object.hpp"

class DrawableObject : public Object, public sf::Transformable, public sf::Drawable
{
    public:
        DrawableObject();
        virtual ~DrawableObject();
        virtual ObjectType GetObjectType() const override;

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif // _DRAWABLEOBJECT_HPP_
