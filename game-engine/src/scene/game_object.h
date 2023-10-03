#pragma once

#include <functional>
#include <unordered_map>
#include <type_traits>
#include <string>
#include "utils/typedefs.h"
#include "scene/component.h"

namespace game_engine
{
	class component;

	class game_object
	{
	public:

		game_object(const std::string& name);

		void update(float delta_time);

		void add_component(component& new_component);

		template<typename T, std::enable_if<std::is_base_of<component, T>::type *= nullptr>>
		T& get_component(id_t id)
		{
			return *static_cast<T*>(&m_components[id]);
		}

		void remove_component(id_t id);

		void start();
		void destroy();
		bool is_dead();

	private:

		std::string m_name;
		bool m_is_dead;
		std::unordered_map<id_t, component&> m_components;
	};
}
