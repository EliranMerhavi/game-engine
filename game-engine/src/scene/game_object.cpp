#include "pch.h"
#include "game_object.h"

namespace game_engine
{
    game_object::game_object(const std::string& name)
        :
        m_name(name),
        m_is_dead(false),
        m_components()
    {
    }

    void game_object::update(float delta_time)
    {
        for (const auto& [key, _component] : m_components)
            _component.update(delta_time);
    }

    void game_object::start()
    {
        for (const auto& [id, _component] : m_components)
            _component.start();
    }

    void game_object::destroy()
    {
        for (const auto& [id, _component] : m_components)
            _component.destroy();
    }

    void game_object::add_component(component& new_component)
    {
        id_t id = new_component.id();

        if (m_components.count(id))
            throw std::exception("component already been added");

        m_components.emplace(id, new_component);
    }

    void game_object::remove_component(id_t id)
    {
        if (!m_components.count(id))
            throw std::exception("component already been added");

        m_components.erase(id);
    }


    bool game_object::is_dead()
    {
        return m_is_dead;
    }
}