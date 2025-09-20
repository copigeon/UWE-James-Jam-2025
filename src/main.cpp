#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game.h"

int main()
{
    std::cout << "You should see a window that opens as well as this writing to console..." << std::endl;

    // create window and set up

    sf::RenderWindow window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode({ 1024, 768 }, desktop.bitsPerPixel), "UWE GAMES JAM 2025");
    window.setFramerateLimit(60);

    //initialise an instance of the game class
    Game game(window);

    //run the init function of the game class and check it all initialises ok
    if (!game.init())
    {
        return 0;
    }

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    std::cout << dt << std::endl;


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) { window.close(); }

            //MOUSE EVENTS

            // mouse button PRESSED event
            if (event->is<sf::Event::MouseButtonPressed>()) { game.mousePressed(event); }
            // mouse button RELEASED event
            if (event->is<sf::Event::MouseButtonReleased>()) { game.mouseReleased(event); }
            // mouse ENTERED event
            if (event->is<sf::Event::MouseEntered>()) { game.mouseEntered(event); }
            // mouse LEFT event
            if (event->is<sf::Event::MouseLeft>()) { game.mouseLeft(event); }
            // mouse MOVED event
            if (event->is<sf::Event::MouseMoved>()) { game.mouseMoved(event); }
            // mouse MOVED event
            if (event->is<sf::Event::MouseMovedRaw>()) { game.mouseMovedRaw(event); }
            // mouse MOVED event
            if (event->is<sf::Event::MouseWheelScrolled>()) { game.mouseWheelScrolled(event); }

            //KEY EVENTS

            // key pressed event
            if (event->is<sf::Event::KeyPressed>()) { game.keyPressed(event); }
            // key released event
            if (event->is<sf::Event::KeyReleased>()) { game.keyReleased(event); }
            // text entry
            if (event->is<sf::Event::TextEntered>()) { game.textEntered(event); }

            //TOUCH EVENTS

            // touch begins event
            if (event->is<sf::Event::TouchBegan>()) { game.touchBegan(event); }
            // touch end event
            if (event->is<sf::Event::TouchEnded>()) { game.touchEnd(event); }
            // touch end event
            if (event->is<sf::Event::TouchMoved>()) { game.touchMoved(event); }

            //JOYSTICK EVENTS

            if (sf::Joystick::isConnected(0) || sf::Joystick::isConnected(1))
            {
                // joystick button moved event
                if (event->is<sf::Event::JoystickMoved>()) { game.joystickMoved(event); }
                // joystick button pressed event
                if (event->is<sf::Event::JoystickButtonPressed>()) { game.JoystickButtonPressed(event); }
                // joystick button released event
                if (event->is<sf::Event::JoystickButtonReleased>()) { game.joystickButtonReleased(event); }
            }

            // joystick button connected event
            if (event->is<sf::Event::JoystickConnected>()) { game.JoystickConnected(event); }
            // joystick button disconnected event
            if (event->is<sf::Event::JoystickDisconnected>()) { game.joystickDisconnected(event); }
        }

        //'update' element of the game loop
        game.update(dt);
        //'render' element of the game loop
        game.render();

        window.display();
    }

    return 0;
}