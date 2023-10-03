#include "pch.h"
#include "component.h"

namespace game_engine
{
	id_t component::s_id_counter = 0;

	component::component() : m_id(s_id_counter++)
	{
	}

	id_t component::id()
	{
		return m_id;
	}
}