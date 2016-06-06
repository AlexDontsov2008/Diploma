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

        default:
            return sf::String(" ");
    }
}


CellImpl::CellImpl(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Vector2u& l_mapCoord, const sf::Font& l_font)
: m_rect()
, m_mark(GetMarkByCellState(m_state), l_font)
, m_mapCoord(l_mapCoord)
, m_state(Cell::PASSABLE)
{
    Init(l_windowPosition, l_sideSize, l_font);
}

CellImpl::~CellImpl()
{}

void CellImpl::Init(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Font& l_font)
{
    m_rect.setSize(sf::Vector2f(l_sideSize, l_sideSize));
    m_rect.setPosition(l_windowPosition);
    m_rect.setFillColor(GetColorByCellState(m_state));
    m_rect.setOutlineThickness(3.f);
    m_rect.setOutlineColor(sf::Color::Black);

    auto cellPosition = m_rect.getPosition();
    m_mark.setPosition(cellPosition.x + l_sideSize / 2.f, cellPosition.y + l_sideSize / 2.f);
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

void CellImpl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect, states);
    target.draw(m_mark, states);
}
