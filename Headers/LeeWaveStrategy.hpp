#ifndef _LEE_WAVE_STRATEGY_HPP_
#define _LEE_WAVE_STRATEGY_HPP_

#include "TrajectoryFindStrategy.hpp"

class LeeWaveStrategy : public TrajectoryFindStrategy
{
    public:
        LeeWaveStrategy();
        virtual ~LeeWaveStrategy();

    public:
        virtual Trajectory TrajectoryFindAlgorithm() override;
};

#endif // _LEE_WAVE_STRATEGY_HPP_
