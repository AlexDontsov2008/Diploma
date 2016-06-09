#ifndef _MOVEABLE_OBJECT_HPP_
#define _MOVEABLE_OBJECT_HPP_

#include <SFML/Graphics.hpp>
#include "Object.hpp"

class MoveableObject : public Object
{
    public:
        struct Locations
        {
            Locations(const sf::Vector2u& l_currentLocation, const sf::Vector2u& l_nextLocation)
            : currentLocation(l_currentLocation)
            , nextLocation(l_nextLocation)
            {}

            sf::Vector2u currentLocation;
            sf::Vector2u nextLocation;
        };

    public:
        MoveableObject();
        virtual ~MoveableObject() {};

        virtual ObjectType GetObjectType() const override;

        sf::Vector2u GetCurrentLocation() const;
        void SetCurrentLocation(const sf::Vector2u& l_currentLocation);

        sf::Vector2u GetNextLocation() const;
        void SetNextLocation(const sf::Vector2u& l_nexLocation);

    private:
        Locations m_locations;
};

inline sf::Vector2u MoveableObject::GetCurrentLocation() const
{
    return m_locations.currentLocation;
}

inline void MoveableObject::SetCurrentLocation(const sf::Vector2u& l_currentLocation)
{
    m_locations.currentLocation = l_currentLocation;
}

inline sf::Vector2u MoveableObject::GetNextLocation() const
{
    return m_locations.nextLocation;
}

inline void MoveableObject::SetNextLocation(const sf::Vector2u& l_nexLocation)
{
    m_locations.nextLocation = l_nexLocation;
}

#endif // _MOVEABLE_OBJECT_HPP_
