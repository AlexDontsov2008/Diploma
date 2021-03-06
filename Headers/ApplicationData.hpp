#ifndef _APPLICATION_DATA_HPP_
#define _APPLICATION_DATA_HPP_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "pugixml.hpp"
#include "Uncopyable.hpp"
#include "Singleton.hpp"

struct ApplicationSettings
{
    ApplicationSettings()
    {
        SetApplicationSettings();
    }

    void SetApplicationSettings(size_t l_windowWidth = 0, size_t l_windowHeight = 0, const std::string& l_windowName = "")
    {
        m_widnowWidth = l_windowWidth;
        m_windowHeight = l_windowHeight;
        m_windowName = l_windowName;
    }

    size_t m_widnowWidth;
    size_t m_windowHeight;
    std::string m_windowName;
};

struct MapSettings
{
    MapSettings()
    {
        SetMapSettings();
    }

    void SetMapSettings(size_t l_mapWidth = 0, size_t l_mapHeight = 0, size_t l_cellSize = 0)
    {
        m_mapWidth = l_mapWidth;
        m_mapHeight = l_mapHeight;
        m_cellSize = l_cellSize;
    }

    size_t m_mapHeight;
    size_t m_mapWidth;
    size_t m_cellSize;
};

struct Locations
{
    Locations()
    {
        SetLocations();
    }

    void SetLocations(const sf::Vector2u& l_source = sf::Vector2u(0, 0),
                      const sf::Vector2u& l_destination = sf::Vector2u(0, 0),
                      const std::vector<sf::Vector2u>& l_enemiesPositions = std::vector<sf::Vector2u>{sf::Vector2u(0, 0)})
    {
        m_source = l_source;
        m_destination = l_destination;
        m_enemiesPositions = l_enemiesPositions;
    }

    sf::Vector2u m_source;
    sf::Vector2u m_destination;
    std::vector<sf::Vector2u> m_enemiesPositions;
};

struct EnemyParams
{
    explicit EnemyParams(const std::vector<sf::Vector2u>& l_translation = std::vector<sf::Vector2u>{sf::Vector2u(0, 0)},
                        size_t l_radiusAttack = 0)
    : translation(l_translation)
    , radiusAttack(l_radiusAttack)
    {}

    void SetEnemyParams(const std::vector<sf::Vector2u>& l_translation, size_t l_radiusAttack)
    {
        translation = l_translation;
        radiusAttack = l_radiusAttack;
    }

    std::vector<sf::Vector2u> translation;
    size_t radiusAttack;
};


class ApplicationData : public Singleton<ApplicationData>
{
    public:
        friend Singleton<ApplicationData>;

        ApplicationData();

        const ApplicationSettings& GetApplicationSettins() const
        {
            return m_applicationSett;
        }

        const MapSettings& GetMapSettings() const
        {
            return m_mapSett;
        }

        const Locations& GetLocations() const
        {
            return m_locations;
        }

        const std::vector<EnemyParams>& GetEnemiesParams() const
        {
            return m_enemiesParams;
        }

    private:
        void ParseParameters(const pugi::xml_document& doc);

    private:
        ApplicationSettings m_applicationSett;
        MapSettings m_mapSett;
        Locations m_locations;
        std::vector<EnemyParams> m_enemiesParams;
};

#endif // _APPLICATION_DATA_HPP_
