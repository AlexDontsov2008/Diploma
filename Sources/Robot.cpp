#include "Robot.hpp"
#include "DiscreteMap.hpp"

Robot::Robot()
: m_trajectoryStep(0)
{
    m_trajectory.push_back(sf::Vector2u(0, 0));
    m_trajectory.push_back(sf::Vector2u(1, 0));
    m_trajectory.push_back(sf::Vector2u(2, 0));
    m_trajectory.push_back(sf::Vector2u(3, 0));
    m_trajectory.push_back(sf::Vector2u(4, 0));
    m_trajectory.push_back(sf::Vector2u(5, 0));
    m_trajectory.push_back(sf::Vector2u(4, 0));
    m_trajectory.push_back(sf::Vector2u(3, 0));
    m_trajectory.push_back(sf::Vector2u(2, 0));
    m_trajectory.push_back(sf::Vector2u(1, 0));

    //SetCurrentLocation(m_trajectory[m_trajectoryStep]);
    //SetNextLocation(m_trajectory[m_trajectoryStep]);
}

Robot::~Robot()
{

}

void Robot::TrajectoryStepIteration()
{
    SetCurrentLocation(GetNextLocation());
    SetNextLocation(m_trajectory[++m_trajectoryStep % m_trajectory.size()]);
}

void Robot::UpdateLocationOnMap(DiscreteMap* l_map) const
{
    if (GetNextLocation() != GetCurrentLocation())
    {
        l_map->SetCellWithPositionAndState(GetNextLocation(), Cell::OCCUPY_BY_ROBOT);
        l_map->SetCellWithPositionAndState(GetCurrentLocation(), Cell::PASSABLE);
    }
    else
    {
        l_map->SetCellWithPositionAndState(GetCurrentLocation(), Cell::OCCUPY_BY_ROBOT);
    }
}

void Robot::Update(sf::Time dt)
{
    TrajectoryStepIteration();
}

Object::ObjectType Robot::GetObjectType() const
{
    return MoveableObject::GetObjectType();
}














