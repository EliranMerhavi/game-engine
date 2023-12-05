#include "pch.h"
#include "game_engine.h"
#include "core/config.h"
#include "core/time.h"
#include "scene/scene_t.h"
#include "core/input.h"
#include "renderer2D/renderer2D.h"


namespace game_engine
{
    bool running;
    config_t config_data;
    scene_t* current_scene;
    GLFWwindow* glfw_window;
}

void game_engine::init(const config_t& config)
{
    assert(config.starting_scene != nullptr);
    assert(config.limitFPS >= 0);
    assert(config.width > 0 && config.height > 0);
    
    config_data = config;
    
    assert(glfwInit() && "error when calling glfwInit()");
    
    glfw_window = glfwCreateWindow(config_data.width, config_data.height, config_data.window_title.c_str(), nullptr, nullptr);

    assert(glfw_window && "error on glfwCreateWindow()");

    glfwMakeContextCurrent(glfw_window);

    GLenum error = glewInit();
  
    if (error != GLEW_OK)
        throw std::exception(("error when calling glewInit()\nerror message: " + std::string((const char*)glewGetErrorString(error))).c_str());

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "[GL ERROR]" : ""),
            type, severity, message);

            if (type == GL_DEBUG_TYPE_ERROR)
            {
                __debugbreak();
            }
        }, 0);
#endif

    glfwSetWindowCloseCallback(glfw_window, [](GLFWwindow* window) {
        running = false;
    });

    input::init();
    renderer2D::init();
    config::set_limitFPS(config.limitFPS);
    config::set_vsync(config_data.vsync);
    set_scene(*config.starting_scene);
}

void game_engine::run()
{
    time_step_t previous_time = time::current();
    running = true;
    while (running)
    {
        renderer2D::clear();

        time_step_t current_time = time::current();
        time::s_delta_time += (current_time - previous_time) / config_data.limitFPS;
        previous_time = current_time;

        if (!current_scene)
            continue;

        if (time::s_delta_time >= 1.0) {
            current_scene->update();
            time::s_delta_time--;
        }

        current_scene->render();
        renderer2D::flush();
        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    renderer2D::shutdown();
    glfwTerminate();
}

void game_engine::set_scene(scene_t& scene)
{
    current_scene = &scene;
    current_scene->on_create();
}

GLFWwindow* game_engine::window()
{
    return glfw_window;
}

int game_engine::config::window_width()
{
    return config_data.width;
}

int game_engine::config::window_height()
{
    return config_data.height;
}

void game_engine::config::set_vsync(bool vsync)
{
	glfwSwapInterval(vsync);
    config_data.vsync = vsync;
}

void game_engine::config::set_limitFPS(float fps)
{
    assert(fps > 0);
    config_data.limitFPS = fps;
}

const config_t& game_engine::config::get_config()
{
    return config_data;
}