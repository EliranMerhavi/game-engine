#include "pch.h"
#include "application.h"
#include "renderer2D/renderer2D.h"

namespace game_engine
{
    application::application()
        :
        m_window(500, 500, "ONLY FOR TEST"),
        m_current_scene(nullptr),
        m_running(true),
        m_previous_time(std::chrono::high_resolution_clock::now())
    {
    }
 
    void application::run()
    {
        if (!renderer2D::has_initialized())
            renderer2D::init();

        renderer2D::set_camera(glm::ortho(0.0f, (float)m_window.width(), (float)m_window.height(), 0.0f, -1.0f, 1.0f));

        while (m_running)
        {
            renderer2D::clear();

            time_point current_time = std::chrono::high_resolution_clock::now();
            float delta_time = std::chrono::duration<float, std::chrono::seconds::period>(current_time - m_previous_time).count();

            if (m_current_scene)
            {
                m_current_scene->update(delta_time);
                m_current_scene->render();
            }
            renderer2D::render();
            m_window.update();
            m_previous_time = current_time;
        }

        renderer2D::shutdown();
        glfwTerminate();
    }

    void application::close()
    {
    }

    void application::on_window_close()
    {
        m_running = false;
    }

    void application::set_current_scene(scene& scene)
    {
        m_current_scene = &scene;
    }

    application& application::instance()
    {
        static application s_instance;
        return s_instance;
    }
}
