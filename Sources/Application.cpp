#include <exception>

#include "Application.hpp"

static constexpr char PathToTheAppData[] = "Resources/ApplicationData.xml";
static constexpr char PathToTheFont[] = "Resources/Sansation.ttf";

Application::Application()
: m_data(PathToTheAppData)
, m_fontStorage(PathToTheFont)
, m_window(m_data.GetApplicationSettins().m_windowName,
           sf::Vector2u(m_data.GetApplicationSettins().m_widnowWidth, m_data.GetApplicationSettins().m_windowHeight))
, m_map(sf::Vector2u(m_data.GetMapSettings().m_mapWidth, m_data.GetMapSettings().m_mapHeigh),
        m_data.GetMapSettings().m_cellSize,
        m_fontStorage.getFont())
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
    m_map.SetCellWithPositionAndState(m_data.GetLocations().m_source, Cell::SOURCE);
    m_map.SetCellWithPositionAndState(m_data.GetLocations().m_destination, Cell::DESTINATION);
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











