#include "pch.h"
#include "input.h"


namespace input
{
    float yoffset;
}

void input::init()
{
    glfwSetScrollCallback(game_engine::window(), [](GLFWwindow* window, double xoffset, double yoffset) {    
        input::yoffset = yoffset;
    });
}

input::state input::key_state(keycode_t code)
{    
    return (state)glfwGetKey(game_engine::window(), code);
}

input::state input::mouse_state(mousecode_t button)
{   
    return (state)glfwGetMouseButton(game_engine::window(), button);
}

float input::mouse_scroll_offset()
{
    float res = yoffset;
    yoffset = 0.0f;
    return res;
}

glm::f32vec2 input::mouse_position()
{
    glm::f64vec2 res;
    glfwGetCursorPos(game_engine::window(), &res.x, &res.y);
    return res;
}
