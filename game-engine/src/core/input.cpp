#include "pch.h"
#include "input.h"

key_state input::get_key_state(keycode_t code)
{
    return (key_state)glfwGetKey(game_engine::window(), code);
}
