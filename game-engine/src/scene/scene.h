#pragma once

namespace game_engine
{
	class scene
	{
	public:
		virtual void on_create() = 0;
		virtual void start() = 0;
		virtual void load_resources() = 0;
		virtual void render() = 0;
		virtual void update() = 0;
		// virtual ~scene() = 0;
	};
}
