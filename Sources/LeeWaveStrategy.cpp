#include <list>

#include "LeeWaveStrategy.hpp"
#include "Application.hpp"
#include "DiscreteMap.hpp"
#include "Robot.hpp"

// Math model of the map
class MapCoord
{
public:
	explicit MapCoord(const sf::Vector2u& l_mapSize)
    : m_mapSize(l_mapSize)
	, m_map(nullptr)
	{
		Initialize();
	}

	~MapCoord()
	{
		for (size_t i = 0; i < m_mapSize.y; ++i)
			delete[] m_map[i];

		delete[] m_map;
	}

	int** SetMap()
	{
		return m_map;
	}

	sf::Vector2u GetMapSize() const
	{
		return m_mapSize;
	}


private:
	void Initialize()
	{
		m_map = new int*[m_mapSize.y];
		for (size_t i = 0; i < m_mapSize.y; ++i)
		{
			m_map[i] = new int[m_mapSize.x];

			for (size_t j = 0; j < m_mapSize.x; ++j)
				m_map[i][j] = m_mapSize.y * m_mapSize.x - 1;
		}
	}


private:
	const sf::Vector2u m_mapSize;
	int** m_map;
};

static void AddEnemies(MapCoord& l_mapModel, const std::vector<std::unique_ptr<Enemy>>& enemies)
{
    const size_t enemyMark = l_mapModel.GetMapSize().x * l_mapModel.GetMapSize().y;
    for (const auto& enemy : enemies)
    {
        auto enemyLocation = enemy->GetLocation();
        l_mapModel.SetMap()[enemyLocation.y][enemyLocation.x] = enemyMark;
    }
}

static void SetSourceAndDestination(MapCoord& l_mapModel, const sf::Vector2u& l_source, const sf::Vector2u& l_destination)
{
    l_mapModel.SetMap()[l_source.y][l_source.x] = 0;
    l_mapModel.SetMap()[l_destination.y][l_destination.x] = -1;
}

// Check if new position != end position
static inline bool IsPositionNotEqualEndPosition(const sf::Vector2u& l_position, const sf::Vector2u& l_destination)
{
	return	(l_position.x + 1 != l_destination.x || l_position.y != l_destination.y) &&
            (l_position.x - 1 != l_destination.x || l_position.y != l_destination.y) &&
            (l_position.x != l_destination.x || l_position.y + 1 != l_destination.y) &&
            (l_position.x != l_destination.x || l_position.y - 1 != l_destination.y);
}

// Check if new position not enemy or  postion already set
static void AddNewPositionToTrajectory(const sf::Vector2i& l_position, std::vector<sf::Vector2u>& trajectory,
                                       MapCoord& l_mapModel, int iter)
{
	const auto mapSize = l_mapModel.GetMapSize();
	const int NotBlocked = mapSize.x * mapSize.y - 1;

	if (l_position.x + 1 < mapSize.x && l_mapModel.SetMap()[l_position.y][l_position.x + 1] == NotBlocked)
	{
		trajectory.push_back(sf::Vector2u(l_position.x + 1, l_position.y));
		l_mapModel.SetMap()[l_position.y][l_position.x + 1] = iter + 1;
	}

	if ((l_position.x - 1 >= 0) && (l_mapModel.SetMap()[l_position.y][l_position.x - 1] == NotBlocked))
	{
		trajectory.push_back(sf::Vector2u(l_position.x - 1, l_position.y));
		l_mapModel.SetMap()[l_position.y][l_position.x - 1] = iter + 1;
	}

	if (l_position.y + 1 < mapSize.y && l_mapModel.SetMap()[l_position.y + 1][l_position.x] == NotBlocked)
	{
		trajectory.push_back(sf::Vector2u(l_position.x, l_position.y + 1));
		l_mapModel.SetMap()[l_position.y + 1][l_position.x] = iter + 1;
	}

	if ((l_position.y - 1 >= 0) && (l_mapModel.SetMap()[l_position.y - 1][l_position.x] == NotBlocked))
	{
		trajectory.push_back(sf::Vector2u(l_position.x, l_position.y - 1));
		l_mapModel.SetMap()[l_position.y - 1][l_position.x] = iter + 1;
	}
}

static void BuildMap(MapCoord& l_mapModel, const sf::Vector2u& l_source, const sf::Vector2u& l_destination)
{
	int iter = 0;
	bool isEndOfSearch = false;

	std::vector<sf::Vector2u> trajectory{ 1, l_source };

	while (true)
	{
		// Create a newTrajectory for save new positions
		std::vector<sf::Vector2u> newTrajectory;

		// Process all points in trajectory
		for (auto position : trajectory)
		{
			if (IsPositionNotEqualEndPosition(position, l_destination))
			{
				// Check if a new position is not blocked, then add it in the newTrajectory
				AddNewPositionToTrajectory(static_cast<sf::Vector2i>(position), newTrajectory, l_mapModel, iter);
			}
			else
			{
				l_mapModel.SetMap()[l_destination.y][l_destination.x] = iter + 1;
				isEndOfSearch = true;
				break;
			}
		}// End of process trajectory

		if (!isEndOfSearch)
		{
			// Increment the iter and move points from newTrajectory to the trajectory
			iter += 1;
			trajectory = std::move(newTrajectory);
		}
		else
		{
			break;
		}
	}
}

static std::list<sf::Vector2u> GetResultTrajectory(MapCoord& l_mapModel, const sf::Vector2u& l_source, const sf::Vector2u& l_destination)
{
	std::list<sf::Vector2u> resultTrajectory{ 1, l_destination };
	const auto mapSize = l_mapModel.GetMapSize();


	while (resultTrajectory.front() != l_source)
	{
		sf::Vector2i position = static_cast<sf::Vector2i>(resultTrajectory.front());
		int value = l_mapModel.SetMap()[position.y][position.x];

		if (position.x - 1 >= 0 && l_mapModel.SetMap()[position.y][position.x - 1] == value - 1)
			resultTrajectory.push_front(sf::Vector2u(position.x - 1, position.y));

		else if (position.x + 1 < mapSize.x && l_mapModel.SetMap()[position.y][position.x + 1] == value - 1)
			resultTrajectory.push_front(sf::Vector2u(position.x + 1, position.y));

		else if (position.y - 1 >= 0 && l_mapModel.SetMap()[position.y - 1][position.x] == value - 1)
			resultTrajectory.push_front(sf::Vector2u(position.x, position.y - 1));

		else if (position.y + 1 < mapSize.y && l_mapModel.SetMap()[position.y + 1][position.x] == value - 1)
			resultTrajectory.push_front(sf::Vector2u(position.x, position.y + 1));
	}

	return resultTrajectory;
}

static void PrintMap(MapCoord& l_mapModel)
{
	const auto mapSize = l_mapModel.GetMapSize();

	for (size_t i = 0; i < mapSize.y; ++i)
	{
		for (size_t j = 0; j < mapSize.x; ++j)
		{
			std::cout.width(3);
			std::cout << l_mapModel.SetMap()[i][j] << ' ';
		}
		std::cout << '\n';
	}

	std::cout.width(1);
	std::cout << std::endl;
}

static void PrintTrajectory(const std::list<sf::Vector2u>& l_trajectory)
{
	int iter{ 0 };
	for (auto position : l_trajectory)
	{
		std::cout << "-> [" << position.x << ", " << position.y << "]";
		iter += 1;

		if (iter % 4 == 0)
			std::cout << '\n';
	}
	std::cout << std::endl;
}

static void PrintResultIntoConsole(MapCoord& l_mapModel, const std::list<sf::Vector2u>& l_trajectory)
{
    PrintMap(l_mapModel);
    PrintTrajectory(l_trajectory);
}


LeeWaveStrategy::LeeWaveStrategy()
{}

LeeWaveStrategy::~LeeWaveStrategy()
{}


LeeWaveStrategy::Trajectory LeeWaveStrategy::TrajectoryFindAlgorithm()
{
    const Application& app = Application::Instance();
    const DiscreteMap& discreteMap = app.GetDiscreteMap();
    const ApplicationData& appData = app.GetApplicationData();
    const auto sourceLocation = Robot::Instance().GetLocation();

    // 1. Create the map model
    MapCoord mapModel(discreteMap.GetMapSize());
    // 2. Add enemies on the map
    AddEnemies(mapModel, Application::Instance().GetEnemies());
    // 3. Add the source and the destination
    SetSourceAndDestination(mapModel, sourceLocation, appData.GetLocations().m_destination);
    // 4. Build the map for the result trajectory
    BuildMap(mapModel, sourceLocation, appData.GetLocations().m_destination);
    // 5. Get the result trajectory
    auto trajectory = GetResultTrajectory(mapModel, sourceLocation, appData.GetLocations().m_destination);
    // 6. Print results.
    PrintResultIntoConsole(mapModel, trajectory);

    trajectory.pop_front();
    return trajectory;
}
