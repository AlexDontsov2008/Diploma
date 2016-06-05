#include <exception>

#include "Application.hpp"
#include "pugixml.hpp"

namespace
{
    constexpr float windowScale = 0.7f;
    const auto descktopMode = sf::VideoMode::getDesktopMode();
    const size_t windowWidth  = descktopMode.width * windowScale;
    const size_t windowHeight = descktopMode.height * windowScale;
    constexpr char windowName[] = "Trajectory Visualisation";
}

Application::Application()
: m_window(windowName, sf::Vector2u(windowWidth, windowHeight))
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
    m_window.EndDraw();
}

void Application::HandleInput()
{

}


void Application::Init()
{

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











