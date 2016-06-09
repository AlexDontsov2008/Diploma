#include "ApplicationData.hpp"

ApplicationData::ApplicationData(const std::string& l_pathToTheFile)
{
    pugi::xml_document doc;
    if (!doc.load_file(l_pathToTheFile.c_str()))
    {
        char buffer[64];
        sprintf(buffer, "Failed to load %s file", l_pathToTheFile.c_str());
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

}

