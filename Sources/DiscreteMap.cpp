#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "DiscreteMap.hpp"

DiscreteMap::DiscreteMap(const sf::Vector2u& l_mapSize, float l_cellSideSize, const sf::Font& l_font)
: m_mapWidth(l_mapSize.x)
, m_mapHeight(l_mapSize.y)
{
    Init(l_cellSideSize, l_font);
}

DiscreteMap::~DiscreteMap()
{

}

void DiscreteMap::Init(float l_cellSideSize, const sf::Font& l_font)
{
    const auto l_mapStartPosition = sf::Vector2f(100.f, 100.f);
    for (size_t i = 0; i < m_mapHeight; ++i)
    {
        std::vector<std::shared_ptr<Cell>> l_rowMatrix;
        for (size_t j = 0; j < m_mapWidth; ++j)
        {
            auto l_cellPosition = l_mapStartPosition;
            l_cellPosition.x += l_cellSideSize * j;
            l_cellPosition.y += l_cellSideSize * i;

            auto l_cellMapCoord = sf::Vector2u(j, i);
            l_rowMatrix.push_back(std::make_shared<Cell>(l_cellPosition, l_cellSideSize, l_cellMapCoord, l_font));
        }

        m_cells.push_back(l_rowMatrix);
    }
}


void DiscreteMap::Update(sf::Time dt)
{

}

Object::ObjectType DiscreteMap::GetObjectType() const
{
    return Object::STATIC_OBJ;
}


void DiscreteMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& l_rowOfCells : m_cells)
    {
        for (const auto& cell : l_rowOfCells)
        {
            target.draw(*cell);
        }
    }
}









