#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics.hpp>
#include "Singleton.hpp"
#include "Window.hpp"
#include "DiscreteMap.hpp"
#include "FontStorage.hpp"

class Application : public Singleton<Application>
{
    public:
        friend Singleton<Application>;
        void Run();

        Window* GetWindow();

    protected:
        Application();
        virtual ~Application() {};

    private:
        void Init();

        void Update(sf::Time dt);
        void Render();
        void HandleInput();

    private:
        FontStorage m_fontStorage;
        Window  m_window;
        DiscreteMap m_map;
};

#endif // _APPLICATION_HPP_
