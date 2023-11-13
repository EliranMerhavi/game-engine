#include "test_scene.h"
#include "ecs/components/rigidBody.h"
#include "scene/game_object.h"
#include "ecs/components.h"
#include "renderer2D/renderer2D_utils.h"

test_scene::test_scene()
{

}

void test_scene::on_create()
{

}




test_scene::~test_scene()
{
	renderer2D::free_texture(texture);
}



