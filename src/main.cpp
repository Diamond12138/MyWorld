#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameApplication.cpp"

int main()
{
    GameApplication app;
    MineEngine::initGL(app);
    app.run();
    return 0;
}