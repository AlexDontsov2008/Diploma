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

void DiscreteMap::SetCellWithPositionAndState(const sf::Vector2u& l_position, Cell::CellState l_state)
{
    // Check for boundaries
    if (l_position.x < 0 || l_position.x > m_mapWidth ||
        l_position.y < 0 || l_position.y > m_mapHeight)
    {
        throw std::logic_error("Cell position is beyond the borders of the map");
    }

    // Check for state
    if (l_state < 0 || l_state >= Cell::CellState::COUNT)
    {
        throw std::logic_error("Cell state is undefined");
    }

    // Check for state matches
    // swap x & y for right acces
    auto cell = m_cells[l_position.y][l_position.x];
    if ( (l_state == Cell::DESTINATION && cell->GetState() == Cell::SOURCE) ||
         (l_state == Cell::SOURCE && cell->GetState() == Cell::DESTINATION) )
    {
        throw std::logic_error("Cell state match the SOURCE and  the DESTINATION");
    }

    cell->SetState(l_state);
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









