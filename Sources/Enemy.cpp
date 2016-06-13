#include <memory>
#include <iostream>

#include "Enemy.hpp"
#include "DiscreteMap.hpp"
#include "ApplicationData.hpp"


Enemy::Enemy(const std::vector<sf::Vector2u>& l_translation, size_t l_attackRadius)
: m_translation(l_translation)
, m_attackRadius(l_attackRadius)
, m_translationStep(0)
{
    UpdateLocationByNextStepOfTranslation();
}

Enemy::~Enemy()
{}

void Enemy::Update(sf::Time dt)
{
    UpdateLocationByNextStepOfTranslation();
}

void Enemy::UpdateLocationOnMap(DiscreteMap* l_map) const
{
    // 2. Update enemy location
    l_map->SetCellWithPositionAndState(m_location, Cell::OCCUPY_BY_ENEMY);
}

void Enemy::UpdateAttackRangeOnMap(DiscreteMap* l_map) const
{
    for (auto attackable_location : m_attackableLocations)
    {
        l_map->SetCellWithPositionAndState(attackable_location, Cell::IMPASSABLE);
    }
}

Object::ObjectType Enemy::GetObjectType() const
{
    return MoveableObject::GetObjectType();
}

void Enemy::UpdateLocationByNextStepOfTranslation()
{
    m_location = m_translation[m_translationStep++ % m_translation.size()];
    GenerateAttackableLocations();
}

void Enemy::GenerateAttackableLocations()
{
    // Clear old attackable locations
    m_attackableLocations.clear();

    auto& appData = ApplicationData::Instance();
    const auto MAP_SIZE = sf::Vector2u(appData.GetMapSettings().m_mapWidth, appData.GetMapSettings().m_mapHeight);
    const auto location = static_cast<sf::Vector2i>(m_location);

    // left/right
    if (location.x - 1 >= 0)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x - 1, location.y));
    }
    if (m_location.x + 1 < MAP_SIZE.x)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x + 1, location.y));
    }

    // top/bottom
    if (location.y - 1 >= 0)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x, location.y - 1));
    }
    if (m_location.y + 1 < MAP_SIZE.y)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x, location.y + 1));
    }

    // top corners
    if (location.x - 1 >= 0 && location.y - 1 >= 0)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x - 1, location.y - 1));
    }
    if (location.x + 1 < MAP_SIZE.x && location.y - 1 >= 0)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x + 1, location.y - 1));
    }

    // top corners
    if (location.x - 1 >= 0 && location.y + 1 < MAP_SIZE.y)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x - 1, location.y + 1));
    }
    if (location.x + 1 < MAP_SIZE.x && location.y + 1 < MAP_SIZE.y)
    {
        m_attackableLocations.push_back(sf::Vector2u(location.x + 1, location.y + 1));
    }
}













