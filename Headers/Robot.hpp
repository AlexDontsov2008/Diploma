#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include <list>

#include "MoveableObject.hpp"
#include "Singleton.hpp"

class DiscreteMap;
class FindTrajectoryStrategy;
class TrajectoryFindStrategy;

class Robot : public Singleton<Robot>, public MoveableObject
{
    public:
        friend class Singleton<Robot>;
        using Trajectory = std::list<sf::Vector2u>;

        virtual void Update(sf::Time dt) override;
        virtual ObjectType GetObjectType() const override;
        virtual void UpdateLocationOnMap(DiscreteMap* l_map) const override;
        void SetTrajectoryFindStrategy(std::shared_ptr<TrajectoryFindStrategy> l_trajectoryStrategyPtr);

    protected:
        Robot();
        virtual ~Robot();

    private:
        void UpdateLocationByNextStepOfTrajectory();

    private:
        Trajectory m_trajectory;
        size_t m_trajectoryStep;
        std::shared_ptr<TrajectoryFindStrategy> m_trajectoryStrategyPtr;
};

#endif // _ROBOT_HPP_
