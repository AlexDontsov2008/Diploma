#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML/Graphics.hpp>
#include "Singleton.hpp"

class Application : public Singleton<Application>
{
    public:
        friend Singleton<Application>;
        void Run();

    protected:
        Application();
        virtual ~Application();

    private:
        void Init();

    private:
        sf::RenderWindow    window_;
};

#endif // _APPLICATION_HPP_
