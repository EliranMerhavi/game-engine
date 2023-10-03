#include "pch.h"
#include "opengl_debug.h"

void GLAPIENTRY opengl::debug::MessageCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "[GL ERROR]" : ""),
		type, severity, message);

	if (type == GL_DEBUG_TYPE_ERROR)
	{
		__debugbreak();
	}
}