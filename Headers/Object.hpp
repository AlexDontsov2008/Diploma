#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "Uncopyable.hpp"

namespace sf
{
    class Time;
}

class Object : private Uncopyable
{
    public:
        enum ObjectType
        {
            NONE_OBJ,
            DRAWABLE_OBJ,
            STATIC_OBJ,
            MOVEABLE_OBJ,
        };

    public:
        Object();
        virtual ~Object() = 0;

        virtual void Update(sf::Time dt) = 0;
        virtual ObjectType GetObjectType() const = 0;
};

#endif // _OBJECT_HPP_
