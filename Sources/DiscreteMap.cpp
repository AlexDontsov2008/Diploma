#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "DiscreteMap.hpp"
#include "Robot.hpp"
#include "Application.hpp"

DiscreteMap::DiscreteMap(const sf::Vector2u& l_mapSize, float l_cellSideSize, const sf::Font& l_font)
: m_mapSize(l_mapSize)
, m_robotRef(Robot::Instance())
{
    Init(l_cellSideSize, l_font);
}

DiscreteMap::~DiscreteMap()
{

}

void DiscreteMap::Init(float l_cellSideSize, const sf::Font& l_font)
{
    // Добавить l_mapStartPosition в xml
    const auto l_mapStartPosition = sf::Vector2f(100.f, 100.f);
    for (size_t i = 0; i < m_mapSize.y; ++i)
    {
        std::vector<std::shared_ptr<Cell>> l_rowMatrix;
        for (size_t j = 0; j < m_mapSize.x; ++j)
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
    ClearMap();
    UpdateSourceAndDestinationOnMap();
    UpdateRobotLocationOnMap();
    UpdateEnemiesLocationOnMap();
}

void DiscreteMap::UpdateRobotLocationOnMap()
{
    m_robotRef.UpdateLocationOnMap(this);
}

Object::ObjectType DiscreteMap::GetObjectType() const
{
    return Object::STATIC_OBJ;
}

void DiscreteMap::SetCellWithPositionAndState(const sf::Vector2u& l_position, Cell::CellState l_state)
{
    // Check for boundaries
    if (!IsPointExistOnMap(l_position))
    {
        throw std::logic_error("Cell position is beyond the borders of the map");
    }

    // Check for a state
    if (l_state < 0 || l_state >= Cell::CellState::COUNT)
    {
        throw std::logic_error("Cell state is undefined");
    }

    // Check for the states matches
    // swap x & y for the right access
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


bool DiscreteMap::IsPointExistOnMap(const sf::Vector2u& l_point) const
{
    return l_point.x >= 0 && l_point.x < m_mapSize.x && l_point.y >= 0 && l_point.y < m_mapSize.y;
}

// Set all Cells into PASSABLE state
void DiscreteMap::ClearMap()
{
    for (const auto& l_rowOfCells : m_cells)
    {
        for (const auto& cell : l_rowOfCells)
        {
            cell->SetState(Cell::PASSABLE);
        }
    }
}

void DiscreteMap::UpdateSourceAndDestinationOnMap()
{
    auto locations = Application::Instance().GetApplicationData().GetLocations();

    // 1. Update Source
    auto source = locations.m_source;
    m_cells[source.y][source.x]->SetState(Cell::SOURCE);

    // 2. Update Destination
    auto destination = locations.m_destination;
    m_cells[destination.y][destination.x]->SetState(Cell::DESTINATION);
}

void DiscreteMap::UpdateEnemiesLocationOnMap()
{
    const std::vector<std::unique_ptr<Enemy>>& enemies = Application::Instance().GetEnemies();
    for (const auto& enemy : enemies)
    {
        enemy->UpdateLocationOnMap(this);
    }
}




