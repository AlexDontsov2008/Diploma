#include <exception>

#include "Application.hpp"

static constexpr PathToTheFile[] = "Resources/ApplicationData.xml"

Application::Application()
: m_fontStorage("Resources/Sansation.ttf")
, m_window("Trajectory Visualisation", sf::Vector2u(1024, 768))
, m_map(sf::Vector2u(20, 20), 30.f, m_fontStorage.getFont())
{
    Init();
}

void Application::Update(sf::Time dt)
{
    m_window.Update(dt);
}

void Application::Render()
{
    m_window.BeginDraw();
    m_window.Draw(m_map);
    m_window.EndDraw();
}

void Application::HandleInput()
{

}


void Application::Init()
{
    // Filling source data
    m_sourceData.sourcePosition = sf::Vector2u(5, 2);
    m_sourceData.destinationPosition = sf::Vector2u(18, 17);



    m_map.SetCellWithPositionAndState(m_sourceData.sourcePosition, Cell::SOURCE);
    m_map.SetCellWithPositionAndState(m_sourceData.destinationPosition, Cell::DESTINATION);
}

void Application::Run()
{
    const sf::Time frameTime = sf::seconds(1.f / 60.f);

    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;

    while (!m_window.IsDone())
    {
        elapsed += clock.restart();

        if (elapsed >= frameTime)
        {
            elapsed -= frameTime;

            HandleInput();
            Update(frameTime);
        }
        Render();
    }
}











