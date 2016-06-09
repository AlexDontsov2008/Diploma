#ifndef _DISCRETEMAP_HPP_
#define _DISCRETEMAP_HPP_

#include <vector>
#include <memory>

#include "DrawableObject.hpp"
#include "Cell.hpp"

class Robot;

typedef std::vector<std::vector<std::shared_ptr<Cell>>> CellMatrix;


class DiscreteMap : public DrawableObject
{
    public:
        DiscreteMap(const sf::Vector2u& l_mapSize, float l_cellSideSize, const sf::Font& l_font);
        virtual ~DiscreteMap();

        virtual void Update(sf::Time dt) override;
        virtual ObjectType GetObjectType() const override;

        void SetCellWithPositionAndState(const sf::Vector2u& l_position, Cell::CellState l_state);
        bool IsPointExistOnMap(const sf::Vector2u& l_point) const;
        sf::Vector2u GetMapSize() const
        {
            return m_mapSize;
        }

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        void Init(float l_cellSideSize, const sf::Font& l_font);
        // Set all Cells into PASSABLE state
        void ClearMap();
        void UpdateRobotLocationOnMap();
        void UpdateSourceAndDestinationOnMap();
        void UpdateEnemiesLocationOnMap();

    private:
        CellMatrix m_cells;
        sf::Vector2u m_mapSize;
        const Robot& m_robotRef;
};

#endif // _DISCRETEMAP_HPP_
