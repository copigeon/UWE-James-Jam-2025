#pragma once

#include "Game.h"


Game::Game(sf::RenderWindow& game_window)
    : window(game_window), menu(game_window)
{
    srand(time(NULL));
}

Game::~Game()
{
}

//INIT

bool Game::init()
{
    audio_manager.initSounds();
    gauge_test.initGaugeVisual(50, 200, 30, 90, 80, 1);
    typecheck_test.initDialogue();
    typecheck_test.initPlayerDialogue();
    typecheck_test.typingChallenge();

    menu.initMenu();

    return true;
}

//UPDATE

void Game::update(float dt)
{
    //std::cout << "pool size " << audio_manager.sfx_pool.size() << std::endl;
    //std::cout << audio_manager.numQueued(PLAYER) << " is in the queue" << std::endl;
    //std::cout << audio_manager.numQueued(audio_manager.getSounds().at("test")) << " is in the queue" << std::endl;
    //std::cout << audio_manager.numQueued(audio_manager.getSounds().at("test")->getType()) << " is in the queue" << std::endl;

    audio_manager.playSounds();
    gauge_test.updateGauge();
    gauge_test.updateGaugeVisual();
    gauge_test.flashBorder();

    //std::cout << "stored string: " << std::string(typecheck_test.getPlayerInput()) << std::endl;

    /*
    tpool.enqueue([] {
        std::cout << "Hello from the thread pool!\n";
        });
    */


    switch (game_state) {
    case MENU:
    {
        //std::cout << "GAMESTATE - MENU" << std::endl;
        //menu.menuAnimate();
        //GRAPHIC LAPSE X Y END 
        menu.animateSlide(FOREGROUND, 0.01, 5, 0, 0, 0);
        menu.flashGraphic(NAME, sf::Color::Magenta, 0.5);
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }

}

// RENDER

void Game::render()
{
    switch (game_state) {
    case MENU:
    {
        //std::cout << "GAMESTATE - MENU" << std::endl;

        menu.menuDraw();

        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;

        window.draw(gauge_test.getGaugeBox());
        window.draw(gauge_test.getGaugeLeft());
        window.draw(gauge_test.getGaugeRight());
        window.draw(gauge_test.getGaugeMarker());

        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        for (auto& text : typecheck_test.getVecChallengeText()) {
            window.draw(text);
        }
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

//EVENTS MOUSE

void Game::mousePressed(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE PRESSED" << std::endl;
    //audio_manager.playSound(test);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        audio_manager.queueSound(audio_manager.getSounds().at("key"));
        std::cout << "stored string: " << std::string(typecheck_test.getPlayerInput()) << std::endl;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        audio_manager.queueSound(audio_manager.getSounds().at("test"));
    }

    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::mouseReleased(std::optional<sf::Event> event)
{

    //std::cout << "EVENT - MOUSE RELEASED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::mouseEntered(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE ENTERED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::mouseLeft(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE LEFT" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::mouseMoved(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE MOVED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::mouseMovedRaw(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE MOVED RAW" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::mouseWheelScrolled(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - MOUSE MOVED RAW" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        gauge_test.pauseGauge(10);
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        typecheck_test.speak();
    }


}

void Game::keyReleased(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - KEY RELEASED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

//EVENTS TEXT ENTERED

void Game::textEntered(std::optional<sf::Event> event)
{
        //TAKES THE STRING AND ADDS TO IT FOR TEXT ENTERED EVENT - NEED TO ACTIVATE THIS IN CERTAIN GAME STATE
        text_entered = event->getIf<sf::Event::TextEntered>()->unicode;
        typecheck_test.recordPLayerInput(text_entered);
}

//EVENTS TOUCH

void Game::touchBegan(std::optional<sf::Event> event)
{
    std::cout << "EVENT - TOUCH BEGAN" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::touchEnd(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - TOUCH END" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::touchMoved(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - TOUCH MOVED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

//EVENTS JOYSTICK

void Game::JoystickButtonPressed(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - JOYSTICK BUTTON PRESSED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::joystickButtonReleased(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - JOYSTICK BUTTON RELEASED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::JoystickConnected(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - JOYSTICK CONNECTED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::joystickDisconnected(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - JOYSTICK DISCONNECTED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
}

void Game::joystickMoved(std::optional<sf::Event> event)
{
    //std::cout << "EVENT - JOYSTICK MOVED" << std::endl;
    switch (game_state) {
    case MENU:
    {
        std::cout << "GAMESTATE - MENU" << std::endl;
        break;
    }
    case INTRO:
    {
        std::cout << "GAMESTATE - INTRO" << std::endl;
        break;
    }
    case PLAYING:
    {
        std::cout << "GAMESTATE - PLAYING" << std::endl;
        break;
    }
    case TYPECHECK:
    {
        std::cout << "GAMESTATE - TYPECHECK" << std::endl;
        break;
    }
    case GAME_WON:
    {
        std::cout << "GAMESTATE - GAME_WON" << std::endl;
        break;
    }
    case GAME_LOST:
    {
        std::cout << "GAMESTATE - GAME_LOST" << std::endl;
        break;
    }
    }
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

