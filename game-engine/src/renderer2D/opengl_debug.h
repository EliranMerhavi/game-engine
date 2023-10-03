#pragma once


namespace opengl
{
	namespace debug
	{
		void GLAPIENTRY
		MessageCallBack(
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam);
	}
}