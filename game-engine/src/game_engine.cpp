#include "pch.h"
#include "game_engine.h"
#include "core/config.h"
#include "core/time.h"
#include "scene/scene.h"
#include "renderer2D/opengl_debug.h"
#include "renderer2D/renderer2D.h"


namespace game_engine
{
    bool running;
    config_t config_data;
    scene* current_scene;
    GLFWwindow* window;

    void init();
    void on_window_close();
}

void game_engine::init()
{
    if (!glfwInit())
        throw std::exception("error when calling glfwInit()");

    window = glfwCreateWindow(config_data.starting_width, config_data.starting_height, config_data.window_title.c_str(), nullptr, nullptr);

    if (!window)
        throw std::exception("error on glfwCreateWindow()");

    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if (error != GLEW_OK)
        throw std::exception(("error when calling glewInit()\nerror message: " + std::string((const char*)glewGetErrorString(error))).c_str());

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl::debug::MessageCallBack, 0);
#endif
    
    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        on_window_close();
    });

    if (!renderer2D::has_initialized())
        renderer2D::init();
    
    config::set_vsync(config_data.vsync);
    running = true;
}

void game_engine::on_window_close()
{
    running = false;
}

void game_engine::run(const config_t& config)
{
    config_data = config;
    init();
    
    float previous_time = glfwGetTime();
    
    while (running)
    {
        renderer2D::clear();

        float current_time = glfwGetTime();
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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer2D::shutdown();
    glfwTerminate();
}

void game_engine::set_scene(scene& scene)
{
    game_engine::current_scene = &scene;
    game_engine::current_scene->on_create();
}

void game_engine::config::set_vsync(bool vsync)
{
	glfwSwapInterval(vsync);
    config_data.vsync = vsync;
}

void game_engine::config::set_limitFPS(float fps)
{
    config_data.limitFPS = fps;
}
