#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <memory>

#include "DrawableObject.hpp"

namespace sf
{
    class Font;
}

class CellImpl;

class Cell : public DrawableObject
{
    public:
        enum CellState
        {
            PASSABLE,
            IMPASSABLE,
            OCCUPY_BY_ROBOT,
            OCCUPY_BY_ENEMY,
            TRAJECTORY_STEP,
            DESTINATION,
        };
    public:
        Cell(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Vector2u& l_mapCoord, const sf::Font& l_font);
        virtual ~Cell();

        virtual void Update(sf::Time dt) override;
        virtual ObjectType GetObjectType() const override;
        void SetState(CellState l_state);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::shared_ptr<CellImpl> m_pImpl;
};

#endif // _CELL_HPP_
