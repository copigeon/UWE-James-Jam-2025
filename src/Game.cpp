#pragma once

#include "Game.h"
#include "audio/Sound.h"
#include "mech/Gauge.h"


Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{
    srand(time(NULL));
}

Game::~Game()
{
}

bool Game::init()
{
    audio_manager.initSounds();

    gauge_test.initGaugeVisual(50, 200, 30, 90, 80);

    return true;
}

void Game::update(float dt)
{
    //std::cout << "pool size " << audio_manager.sfx_pool.size() << std::endl;
    //std::cout << audio_manager.numQueued(PLAYER) << " is in the queue" << std::endl;
    //std::cout << audio_manager.numQueued(audio_manager.getSounds().at("test")) << " is in the queue" << std::endl;
    //std::cout << audio_manager.numQueued(audio_manager.getSounds().at("test")->getType()) << " is in the queue" << std::endl;

    audio_manager.playSounds();
    gauge_test.updateGaugeVisual();
    gauge_test.flashBorder();

    /*
    tpool.enqueue([] {
        std::cout << "Hello from the thread pool!\n";
        });
    */
}

void Game::render()
{
    window.draw(gauge_test.getGaugeBox());
    window.draw(gauge_test.getGaugeLeft());
    window.draw(gauge_test.getGaugeRight());
    window.draw(gauge_test.getGaugeMarker());
}

//EVENTS MOUSE

void Game::mousePressed(std::optional<sf::Event> event)
{
    std::cout << "EVENT - MOUSE PRESSED" << std::endl;
    //audio_manager.playSound(test);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        audio_manager.queueSound(audio_manager.getSounds().at("key"));
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        audio_manager.queueSound(audio_manager.getSounds().at("test"));
    }

  
}

void Game::mouseReleased(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE RELEASED" << std::endl;
}

void Game::mouseEntered(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE ENTERED" << std::endl;
}

void Game::mouseLeft(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE LEFT" << std::endl;
}

void Game::mouseMoved(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE MOVED" << std::endl;
}

void Game::mouseMovedRaw(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE MOVED RAW" << std::endl;
}

void Game::mouseWheelScrolled(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE MOVED RAW" << std::endl;
}

//EVENTS KEYBOARD

void Game::keyPressed(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - KEY PRESSED" << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        gauge_test.updateGauge(10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        gauge_test.switchFillOrEmpty(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        gauge_test.switchFillOrEmpty(false);
    }
}

void Game::keyReleased(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - KEY RELEASED" << std::endl;
}

//EVENTS TOUCH

void Game::touchBegan(std::optional<sf::Event> event)
{
    std::cout << "EVENT - TOUCH BEGAN" << std::endl;
}

void Game::touchEnd(std::optional<sf::Event> event)
{
    std::cout << "EVENT - TOUCH END" << std::endl;
}

void Game::touchMoved(std::optional<sf::Event> event)
{
    std::cout << "EVENT - TOUCH MOVED" << std::endl;
}

//EVENTS JOYSTICK

void Game::JoystickButtonPressed(std::optional<sf::Event> event)
{
    std::cout << "EVENT - JOYSTICK BUTTON PRESSED" << std::endl;
}

void Game::joystickButtonReleased(std::optional<sf::Event> event)
{
    std::cout << "EVENT - JOYSTICK BUTTON RELEASED" << std::endl;
}

void Game::JoystickConnected(std::optional<sf::Event> event)
{
    std::cout << "EVENT - JOYSTICK CONNECTED" << std::endl;
}

void Game::joystickDisconnected(std::optional<sf::Event> event)
{
    std::cout << "EVENT - JOYSTICK DISCONNECTED" << std::endl;
}

void Game::joystickMoved(std::optional<sf::Event> event)
{
    std::cout << "EVENT - JOYSTICK MOVED" << std::endl;
}

/*
    switch (game_state)
    {
    case MENU:
        std::cout << "This is KEYRELEASED MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is KEYRELEASED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        std::cout << "This is KEYRELEASED PLAYING GAMESTATE" << std::endl;
        break;
    case GAME_WON:
        std::cout << "This is KEYRELEASED GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is KEYRELEASED GAME_LOST GAMESTATE" << std::endl;
        break;
    case PAUSE:
        std::cout << "This is KEYRELEASED GAME_LOST GAMESTATE" << std::endl;
        break;
    }
    */

