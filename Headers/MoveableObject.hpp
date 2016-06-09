#ifndef _MOVEABLE_OBJECT_HPP_
#define _MOVEABLE_OBJECT_HPP_

#include <SFML/Graphics.hpp>
#include "Object.hpp"

class DiscreteMap;

class MoveableObject : public Object
{
    public:
        struct Location
        {
            Location(const sf::Vector2u& l_location)
            : location(l_location)
            {}

            sf::Vector2u location;
        };

    public:
        MoveableObject();
        virtual ~MoveableObject() {};

        virtual void UpdateLocationOnMap(DiscreteMap* l_map) const = 0;
        virtual ObjectType GetObjectType() const override;

        sf::Vector2u GetLocation() const;
        void SetLocation(const sf::Vector2u& l_location);

    protected:
        Location m_location;
};

inline sf::Vector2u MoveableObject::GetLocation() const
{
    return m_location.location;
}

inline void MoveableObject::SetLocation(const sf::Vector2u& l_location)
{
    m_location.location = l_location;
}

#endif // _MOVEABLE_OBJECT_HPP_
