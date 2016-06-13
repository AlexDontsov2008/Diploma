#include "ApplicationData.hpp"

static constexpr char PathToTheAppData[] = "Resources/ApplicationData.xml";

ApplicationData::ApplicationData()
{
    pugi::xml_document doc;
    if (!doc.load_file(PathToTheAppData))
    {
        char buffer[64];
        sprintf(buffer, "Failed to load %s file", PathToTheAppData);
        throw std::logic_error(buffer);
    }

    ParseParameters(doc);
}

void ApplicationData::ParseParameters(const pugi::xml_document& doc)
{
    // Parse application settings
    auto applicationNode = doc.child("Application");
    size_t windowWidth = applicationNode.attribute("windowWidth").as_uint();
    size_t windowHeight = applicationNode.attribute("windowHeight").as_uint();
    const std::string windowName = applicationNode.attribute("windowName").as_string();
    m_applicationSett.SetApplicationSettings(windowWidth, windowHeight, windowName);

    // Parse map settings
    auto mapNode = applicationNode.child("Map");
    size_t mapWidth = mapNode.attribute("mapWidthInCells").as_uint();
    size_t mapHeight = mapNode.attribute("mapHeighInCells").as_uint();
    size_t cellSize = mapNode.attribute("cellSizeInPixel").as_uint();
    m_mapSett.SetMapSettings(mapWidth, mapHeight, cellSize);

    // Parse locations
    auto locationsNode = applicationNode.child("Locations");
    auto sourceNode = locationsNode.child("Source");
    auto destinationNode = locationsNode.child("Destination");
    m_locations.SetLocations(sf::Vector2u(sourceNode.attribute("xPos").as_uint(), sourceNode.attribute("yPos").as_uint()),
                             sf::Vector2u(destinationNode.attribute("xPos").as_uint(), destinationNode.attribute("yPos").as_uint()));

    // Parse enemies params
    auto enemiesNode = applicationNode.child("Enemies");
    for (auto enemyNode = enemiesNode.child("Enemy"); enemyNode; enemyNode = enemyNode.next_sibling("Enemy"))
    {
        size_t radiusAttack = enemyNode.attribute("attackRange").as_uint();
        std::vector<sf::Vector2u> translation;
        for (auto translationNode = enemyNode.child("Translation"); translationNode; translationNode = translationNode.next_sibling("Translation"))
        {
            auto step = sf::Vector2u(translationNode.attribute("xPos").as_uint(), translationNode.attribute("yPos").as_uint());
            translation.push_back(step);
        }

        EnemyParams enemyParams(std::vector<sf::Vector2u>{translation}, radiusAttack);
        m_enemiesParams.push_back(enemyParams);
    }
}

