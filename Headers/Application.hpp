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
        struct SourceData
        {
            sf::Vector2u sourcePosition;
            sf::Vector2u destinationPosition;
        };

    public:
        friend Singleton<Application>;
        void Run();

        const SourceData& GetSourceData() const;

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
        SourceData m_sourceData;
};

inline const Application::SourceData& Application::GetSourceData() const
{
    return m_sourceData;
}

#endif // _APPLICATION_HPP_
