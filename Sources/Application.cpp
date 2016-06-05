#include "Application.hpp"

#include <exception>

namespace
{
    constexpr size_t windowWidth  = 1024;
    constexpr size_t windowHeight = 768;
    constexpr char windowName[] = "Trajectory Visualisation";
}

Application::Application()
: window_ {sf::VideoMode(windowWidth, windowHeight), windowName}
{
    Init();
}

Application::~Application()
{

}

void Application::Init()
{

}

void Application::Run()
{
    sf::RectangleShape rectange(sf::Vector2f(200.f, 200.f));
    rectange.setFillColor(sf::Color::Blue);
    rectange.setPosition(sf::Vector2f(windowWidth / 2.f, windowHeight / 2.f));

    while (window_.isOpen())
    {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        window_.clear(sf::Color::Black);

        window_.draw(rectange);
        window_.display();
    }
}
