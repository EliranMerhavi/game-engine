#include "test_scene.h"
#include "scene/game_object_t.h"
#include "scene/components.h"
#include "glm/gtx/rotate_vector.hpp"

test_scene::test_scene()
{
}

void test_scene::on_create()
{
	game_object_t obj = create_game_object();
	
	obj.add<component::render_callback>(obj, [](game_object_t& obj) {
		auto& transform = obj.get<component::transform>();
		glm::f32vec2 to = { 0, 0.5 };
				
		to = glm::rotate(to, transform.rotation());
		renderer2D::set_color({ 1, 0, 0, 1 });
		renderer2D::circle(transform.matrix());
		renderer2D::line({ 0, 0 }, to);
		
		transform.set_rotation(transform.rotation() + 0.001);
	});
}

test_scene::~test_scene()
{	
}