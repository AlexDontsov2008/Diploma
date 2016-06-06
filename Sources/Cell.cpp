#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Cell.hpp"
#include "CellImpl.hpp"

Cell::Cell(const sf::Vector2f& l_windowPosition, float l_sideSize, const sf::Vector2u& l_mapCoord, const sf::Font& l_font)
: m_pImpl(new CellImpl(l_windowPosition, l_sideSize, l_mapCoord, l_font))
{}

Cell::~Cell()
{}

void Cell::Update(sf::Time dt)
{
    m_pImpl->Update(dt);
}

Object::ObjectType Cell::GetObjectType() const
{
    return m_pImpl->GetObjectType();
}

void Cell::SetState(Cell::CellState l_state)
{
    m_pImpl->SetState(l_state);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_pImpl->draw(target, states);
}
