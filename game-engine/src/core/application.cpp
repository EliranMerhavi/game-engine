#include "pch.h"
#include "application.h"
#include "renderer2D/renderer2D.h"
#include "time.h"

namespace game_engine
{
    application::application()
        :
        m_window(500, 500, "ONLY FOR TEST"),
        m_current_scene(nullptr),
        m_running(true)
    {
    }
 
    void application::run()
    {
        if (!renderer2D::has_initialized())
            renderer2D::init();

        
        renderer2D::set_camera(glm::ortho(0.0f, (float)m_window.width(), (float)m_window.height(), 0.0f, -1.0f, 1.0f));
        
        time_point previous_time = glfwGetTime();
        
        while (m_running)
        {
            
            renderer2D::clear();
            renderer2D::set_camera(glm::ortho(0.0f, (float)m_window.width(), (float)m_window.height(), 0.0f, -1.0f, 1.0f));
            
            time_point current_time = glfwGetTime();
            time::delta_time = current_time - previous_time;

            if (m_current_scene)
            {
                m_current_scene->update();
                m_current_scene->render();
            }
            renderer2D::flush();
            m_window.update();
            previous_time = current_time;
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

    void application::set_vsync(bool val)
    {
        glfwSwapInterval(val);
    }

    application& application::instance()
    {
        static application s_instance;
        return s_instance;
    }
}
