#include <exception>

#include "Application.hpp"
#include "Singleton.hpp"

int main(int argc, char* argv[])
{
    try
    {
        Application& app = Application::Instance();
        app.Run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    return EXIT_SUCCESS;
}
