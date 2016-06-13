#include <exception>

#include "Application.hpp"
#include "Robot.hpp"

static constexpr char PathToTheFont[] = "Resources/Sansation.ttf";

Application::Application()
: m_dataRef(ApplicationData::Instance())
, m_fontStorage(PathToTheFont)
, m_window(m_dataRef.GetApplicationSettins().m_windowName,
           sf::Vector2u(m_dataRef.GetApplicationSettins().m_widnowWidth, m_dataRef.GetApplicationSettins().m_windowHeight))
, m_map(sf::Vector2u(m_dataRef.GetMapSettings().m_mapWidth, m_dataRef.GetMapSettings().m_mapHeight),
        m_dataRef.GetMapSettings().m_cellSize,
        m_fontStorage.getFont())
, m_robotRef(Robot::Instance())
, m_enemies()
{
    Init();
}

void Application::Update(sf::Time dt)
{
    m_window.Update(dt);
    m_map.Update(dt);
    m_robotRef.Update(dt);
    for (const auto& enemy : m_enemies)
    {
        enemy->Update(dt);
    }
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
    // Init the Source and Destination points
    m_map.SetCellWithPositionAndState(m_dataRef.GetLocations().m_source, Cell::SOURCE);
    m_map.SetCellWithPositionAndState(m_dataRef.GetLocations().m_destination, Cell::DESTINATION);

    // Init the Robot location
    m_robotRef.SetLocation(m_dataRef.GetLocations().m_source);
    m_map.SetCellWithPositionAndState(m_robotRef.GetLocation(), Cell::OCCUPY_BY_ROBOT);

    // Init Enemies locations
    auto enemiesParams = m_dataRef.GetEnemiesParams();
    for (auto enemyParams : enemiesParams)
    {
        std::unique_ptr<Enemy> enemy(new Enemy(enemyParams.translation, enemyParams.radiusAttack));
        m_map.SetCellWithPositionAndState(enemy->GetLocation(), Cell::OCCUPY_BY_ENEMY);
        m_enemies.push_back(std::move(enemy));

    }
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
            // Вынести время sleep в xml
            sf::sleep(sf::seconds(1.0f));
        }
        Render();
    }
}











