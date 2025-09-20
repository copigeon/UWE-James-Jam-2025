#pragma once
#include "audio/Sound.h"

struct SoundStruct {
    sf::Sound struct_sfsound;
    std::shared_ptr<Sound> struct_sound;
    bool started = false;

    std::chrono::steady_clock::time_point last_play = std::chrono::steady_clock::time_point::min();
};