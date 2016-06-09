#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CellImpl.hpp"

static sf::Color GetColorByCellState(Cell::CellState state)
{
    switch (state)
    {
        case Cell::PASSABLE:
            return sf::Color::Green;

        case Cell::IMPASSABLE:
            return sf::Color::Magenta;

        case Cell::OCCUPY_BY_ROBOT:
            return sf::Color::Blue;

        case Cell::OCCUPY_BY_ENEMY:
            return sf::Color::Red;

        case Cell::TRAJECTORY_STEP:
            return sf::Color::Yellow;

        case Cell::DESTINATION:
            return sf::Color::Cyan;

        case Cell::SOURCE:
            return sf::Color(147, 19, 207);

        default:
            return sf::Color::Black;
    }
}

static sf::String GetMarkByCellState(Cell::CellState state)
{
    switch (state)
    {
        case Cell::OCCUPY_BY_ROBOT:
            return sf::String("R");

        case Cell::OCCUPY_BY_ENEMY:
            return sf::String("E");

        case Cell::DESTINATION:
            return sf::String("D");

        case Cell::SOURCE:
            return sf::String("S");

        default:
            return sf::String(" ");
    }
}


CellImpl::CellImpl(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Vector2u& l_mapCoord, const sf::Font& l_font)
: m_rect()
, m_mark(GetMarkByCellState(Cell::PASSABLE), l_font)
, m_mapCoord(l_mapCoord)
, m_state(Cell::PASSABLE)
{
    Init(l_windowPosition, l_sideSize, l_font);
}

CellImpl::~CellImpl()
{}

void CellImpl::Init(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Font& l_font)
{
    constexpr float outlineThickness { 3.f };
    m_rect.setSize(sf::Vector2f(l_sideSize, l_sideSize));
    m_rect.setPosition(l_windowPosition);
    m_rect.setFillColor(GetColorByCellState(m_state));
    m_rect.setOutlineThickness(outlineThickness);
    m_rect.setOutlineColor(sf::Color::Black);

    auto cellPosition = m_rect.getPosition();

    m_mark.setPosition(cellPosition.x + outlineThickness, cellPosition.y - outlineThickness * 1.5f);
    m_mark.setColor(sf::Color::White);

}

void CellImpl::Update(sf::Time dt)
{

}

Object::ObjectType CellImpl::GetObjectType() const
{
    return Object::STATIC_OBJ;
}

void CellImpl::SetState(Cell::CellState l_state)
{
    m_state = l_state;
    m_rect.setFillColor(GetColorByCellState(m_state));
    m_mark.setString(GetMarkByCellState(m_state));
}

Cell::CellState CellImpl::GetState() const
{
    return m_state;
}

void CellImpl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect, states);
    target.draw(m_mark, states);
}
