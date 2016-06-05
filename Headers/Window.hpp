#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string>
#include <SFML/Graphics.hpp>


class Window
{
    public:
        Window();
        Window(const std::string& l_title, const sf::Vector2u l_size);
        ~Window();

        void BeginDraw();
        void EndDraw();

        void Update(sf::Time dt);

        bool IsDone() const { return m_isDone; }
        bool IsFullscreen() const { return m_isFullscreen; }
        sf::Vector2u GetWindowSize() const { return m_windowSize; }
        void ToggleFullscreen();

        void Draw(sf::Drawable& a_drawable);

    private:
        void Setup(const std::string& l_title, const sf::Vector2u& l_size);
        void Destroy();
        void Create();

    private:
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_isDone;
        bool m_isFullscreen;
};

#endif // _WINDOW_HPP_
