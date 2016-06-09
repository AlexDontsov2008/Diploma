#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics.hpp>
#include "Singleton.hpp"
#include "Window.hpp"
#include "DiscreteMap.hpp"
#include "FontStorage.hpp"
#include "ApplicationData.hpp"

class Application : public Singleton<Application>
{
    public:
        friend Singleton<Application>;
        void Run();

        const ApplicationData& GetApplicationData() const;

    protected:
        Application();
        virtual ~Application() {};

    private:
        void Init();

        void Update(sf::Time dt);
        void Render();
        void HandleInput();

    private:
        ApplicationData m_data;
        FontStorage m_fontStorage;
        Window  m_window;
        DiscreteMap m_map;
};

inline const ApplicationData& Application::GetApplicationData() const
{
    return m_data;
}

#endif // _APPLICATION_HPP_
