#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics.hpp>

#include "Singleton.hpp"
#include "Window.hpp"
#include "DiscreteMap.hpp"
#include "FontStorage.hpp"
#include "ApplicationData.hpp"
#include "Enemy.hpp"

class Robot;

class Application : public Singleton<Application>
{
    public:
        using Enemies = std::vector<std::unique_ptr<Enemy>>;
        friend Singleton<Application>;
        void Run();

        const ApplicationData& GetApplicationData() const;
        const Enemies& GetEnemies() const;

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
        Robot& m_robotRef;
        Enemies m_enemies;
};

inline const ApplicationData& Application::GetApplicationData() const
{
    return m_data;
}

inline const Application::Enemies& Application::GetEnemies() const
{
    return m_enemies;
}

#endif // _APPLICATION_HPP_
