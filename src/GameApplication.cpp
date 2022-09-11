#include "MineEngine.hpp"

class GameApplication : public MineEngine::Application
{
    public:
    GameApplication() : MineEngine::Application(sf::VideoMode(1280,1024),"Game",sf::Style::Fullscreen) {}

    public:
    virtual void onDisplay()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0,0.0,1.0,1.0);
    }
};