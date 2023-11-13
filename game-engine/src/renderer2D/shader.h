#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <string>

namespace opengl
{
	class shader
	{
	public:
		shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);
		~shader();

		void bind() const;
		void set_uniform_1i(const char* name, int value);
		void set_uniform_4f(const char* name, const glm::f32vec4& vec);
		void set_uniform_4f(const char* name, float v1, float v2, float v3, float v4);

		void set_uniform_mat_4f(const char* name, const glm::mat4& mat);
		void set_uniform_mat_3f(const char* name, const glm::mat3& mat);
		void set_uniform_1iv(const char* name, size_t count, int* value);
		int32_t get_uniform_location(const char* name);

	private:
		static const char* load_shader(const std::string& filepath);
		static uint32_t compile_shader(uint32_t type, const char* source);
	private:
		uint32_t m_rendererID;
		std::unordered_map<const char*, int32_t> m_uniform_cache;
	};
}