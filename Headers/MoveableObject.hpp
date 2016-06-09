#ifndef _MOVEABLE_OBJECT_HPP_
#define _MOVEABLE_OBJECT_HPP_

#include <SFML/Graphics.hpp>
#include "Object.hpp"

class DiscreteMap;

class MoveableObject : public Object
{
    public:
        using Location = sf::Vector2u;

    public:
        MoveableObject();
        virtual ~MoveableObject() {};

        virtual void UpdateLocationOnMap(DiscreteMap* l_map) const = 0;
        virtual ObjectType GetObjectType() const override;

        sf::Vector2u GetLocation() const;
        void SetLocation(const sf::Vector2u& l_location);

    protected:
        Location m_location;
        std::vector<sf::Vector2u> m_trajectory;
        size_t m_trajectoryStep;
};

inline sf::Vector2u MoveableObject::GetLocation() const
{
    return m_location;
}

inline void MoveableObject::SetLocation(const sf::Vector2u& l_location)
{
    m_location = l_location;
}

#endif // _MOVEABLE_OBJECT_HPP_
