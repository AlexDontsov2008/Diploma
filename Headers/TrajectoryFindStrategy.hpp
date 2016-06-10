#ifndef _TRAJECTORY_FIND_STRATEGY_HPP_
#define _TRAJECTORY_FIND_STRATEGY_HPP_

#include <list>
#include <SFML/Graphics.hpp>

#include "Uncopyable.hpp"

class TrajectoryFindStrategy : public Uncopyable
{
    public:
        TrajectoryFindStrategy();
        virtual ~TrajectoryFindStrategy();

    public:
        using Trajectory = std::list<sf::Vector2u>;
        virtual Trajectory TrajectoryFindAlgorithm() = 0;
};

#endif // _TRAJECTORY_FIND_STRATEGY_HPP_
