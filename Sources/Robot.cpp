#include "Robot.hpp"
#include "DiscreteMap.hpp"
#include "Application.hpp"

Robot::Robot()
: m_trajectoryStep(0)
{
    // ЗАМЕНИТЬ на траекторию
    m_trajectory.push_back(sf::Vector2u(5, 0));
    UpdateLocationByNextStepOfTrajectory();
}

Robot::~Robot()
{

}

void Robot::UpdateLocationByNextStepOfTrajectory()
{
    m_location = m_trajectory[m_trajectoryStep++ % m_trajectory.size()];
}

void Robot::UpdateLocationOnMap(DiscreteMap* l_map) const
{
    l_map->SetCellWithPositionAndState(m_location, Cell::OCCUPY_BY_ROBOT);
}

void Robot::Update(sf::Time dt)
{
    UpdateLocationByNextStepOfTrajectory();
}

Object::ObjectType Robot::GetObjectType() const
{
    return MoveableObject::GetObjectType();
}














