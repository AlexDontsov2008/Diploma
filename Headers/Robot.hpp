#ifndef _ROBOT_HPP_
#define _ROBOT_HPP_

#include "MoveableObject.hpp"
#include "Singleton.hpp"

class DiscreteMap;

class Robot : public Singleton<Robot>, public MoveableObject
{
    public:
        friend class Singleton<Robot>;

        virtual void Update(sf::Time dt) override;
        virtual ObjectType GetObjectType() const override;
        virtual void UpdateLocationOnMap(DiscreteMap* l_map) const override;

    protected:
        Robot();
        virtual ~Robot();

    private:
        void TrajectoryStepIteration();

    private:
        std::vector<sf::Vector2u> m_trajectory;
        size_t m_trajectoryStep;
};

#endif // _ROBOT_HPP_
