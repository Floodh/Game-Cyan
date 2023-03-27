#include "KeyboardKey.hpp"

KeyboardKey::KeyboardKey(SDL_Keycode keycode)
    : keycode{keycode}, keydown{false}, keyup{false}, keypress{false}
{}


