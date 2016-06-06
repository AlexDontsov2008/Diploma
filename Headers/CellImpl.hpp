#ifndef CELLIMPL_HPP_
#define CELLIMPL_HPP_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "DrawableObject.hpp"
#include "Cell.hpp"

class CellImpl : public DrawableObject
{
    public:
        CellImpl(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Vector2u& l_mapCoord, const sf::Font& l_font);
        virtual ~CellImpl();

        virtual void Update(sf::Time dt) override;
        virtual ObjectType GetObjectType() const override;
        void SetState(Cell::CellState l_state);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        void Init(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Font& l_font);

    private:
        sf::RectangleShape m_rect;
        sf::Text m_mark;
        sf::Vector2u m_mapCoord;
        Cell::CellState m_state;
};

#endif // CELLIMPL_HPP_
