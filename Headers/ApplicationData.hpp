#ifndef _APPLICATION_DATA_HPP_
#define _APPLICATION_DATA_HPP_

class ApplicationData
{
    public:
        ApplicationData(const std::string& l_pathToTheFile);

    private:
        sf::Vector2u m_source;
        sf::Vector2u m_destination;
        std::vector<sf::Vector2u> m_enemiesPositions;
};

#endif // _APPLICATION_DATA_HPP_
