#ifndef __mine_engine_application_hpp__
#define __mine_engine_application_hpp__

#include <SFML/Graphics.hpp>
#include <memory>

namespace MineEngine
{
    class Application
    {
    private:
        std::unique_ptr<sf::RenderWindow> m_window;

    public:
        static const unsigned int DEFAULT_CONTEXT_ATTRIBUTES = sf::ContextSettings::Attribute::Core | sf::ContextSettings::Attribute::Debug;

    public:
        Application(sf::VideoMode mode, const sf::String &title = "Application", sf::Uint32 style = sf::Style::Default, const sf::ContextSettings &settings = sf::ContextSettings(16, 8, 4, 3, 3, DEFAULT_CONTEXT_ATTRIBUTES, false)) : m_window(std::make_unique<sf::RenderWindow>(mode, title, style, settings)) {}

    public:
        Application &setWindow(sf::RenderWindow *window)
        {
            m_window = std::unique_ptr<sf::RenderWindow>(window);
            return *this;
        }

        sf::RenderWindow &getWindow()
        {
            return *(m_window.get());
        }

    public:
        virtual void run()
        {
            onCreated();
            sf::Event event;
            while (m_window->isOpen())
            {
                while (m_window->pollEvent(event))
                {
                    onEvent(event);
                }

                onDisplay();
                m_window->display();
            }
            quit();
        }

        virtual void quit(int code = EXIT_SUCCESS)
        {
            onDestroyed();
            m_window->close();
            exit(code);
        }

    public:
        virtual void onCreated()
        {
        }

        virtual void onEvent(sf::Event event)
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                quit();
                break;
            case sf::Event::EventType::KeyPressed:
            case sf::Event::EventType::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Key::Escape:
                    quit();
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        virtual void onDisplay()
        {
        }

        virtual void onDestroyed()
        {
        }
    };
} // namespace MineEngine

#endif