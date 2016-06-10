#include "Robot.hpp"
#include "DiscreteMap.hpp"
#include "Application.hpp"
#include "TrajectoryFindStrategy.hpp"
#include "LeeWaveStrategy.hpp"

Robot::Robot()
: m_trajectoryStep(0)
, m_trajectoryStrategyPtr(std::make_shared<LeeWaveStrategy>())
{
    UpdateLocationByNextStepOfTrajectory();
}

Robot::~Robot()
{

}

void Robot::UpdateLocationByNextStepOfTrajectory()
{
    m_location = m_trajectory.front();
}

void Robot::UpdateLocationOnMap(DiscreteMap* l_map) const
{
    l_map->SetCellWithPositionAndState(m_location, Cell::OCCUPY_BY_ROBOT);
}

void Robot::Update(sf::Time dt)
{
    m_trajectory = m_trajectoryStrategyPtr->TrajectoryFindAlgorithm();
    UpdateLocationByNextStepOfTrajectory();
}

Object::ObjectType Robot::GetObjectType() const
{
    return MoveableObject::GetObjectType();
}

void Robot::SetTrajectoryFindStrategy(std::shared_ptr<TrajectoryFindStrategy> l_trajectoryStrategyPtr)
{
    m_trajectoryStrategyPtr = l_trajectoryStrategyPtr;
}













