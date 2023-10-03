#include "pch.h"
#include "shader.h"

opengl::shader::shader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
{
	const char* vertex_src = load_shader(vertex_shader_filepath);
	const char* fragment_src = load_shader(fragment_shader_filepath);

	m_rendererID = glCreateProgram();
	
	GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_src);
	GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_src);

	delete[] vertex_src;
	delete[] fragment_src;

	glAttachShader(m_rendererID, vs);
	glAttachShader(m_rendererID, fs);

	glLinkProgram(m_rendererID);
	glValidateProgram(m_rendererID);
	
	glDeleteShader(vs);
	glDeleteShader(fs);
}

opengl::shader::~shader()
{
	glDeleteProgram(m_rendererID);
}

void opengl::shader::bind() const
{
	glUseProgram(m_rendererID);
}

void opengl::shader::set_uniform_1i(const char* name, int value)
{
	glUniform1i(get_uniform_location(name), value);
}

void opengl::shader::set_uniform_4f(const char* name, const glm::f32vec4& vec)
{
	glUniform4f(get_uniform_location(name), vec[0], vec[1], vec[2], vec[3]);
}

void opengl::shader::set_uniform_4f(const char* name, float v1, float v2, float v3, float v4)
{
	glUniform4f(get_uniform_location(name), v1, v2, v3, v4);
}

void opengl::shader::set_uniform_mat_4f(const char* name, const glm::mat4& mat)
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &mat[0][0]);
}

int32_t opengl::shader::get_uniform_location(const char* name)
{
	if (m_uniform_cache.find(name) == m_uniform_cache.end())
		m_uniform_cache[name] = glGetUniformLocation(m_rendererID, name);

	return m_uniform_cache[name];
}

const char* opengl::shader::load_shader(const std::string& filepath)
{
	FILE* fp;
	char* buff;
	fopen_s(&fp, filepath.c_str(), "rb");
	
	assert(fp, "[ERROR] when opening file \"" + filepath + "\" to load shader\n");

	fseek(fp, 0, SEEK_END);
	size_t length = ftell(fp);
	rewind(fp);
	buff = new char[length + 1];
	fread(buff, sizeof(char), length, fp);
	fclose(fp);
	buff[length] = '\0';

	return buff;
}

uint32_t opengl::shader::compile_shader(uint32_t type, const char* source)
{
	uint32_t id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);
	int32_t result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* msg = new char[length];

		glGetShaderInfoLog(id, length, &length, msg);
		throw std::exception((std::string("failed to compile shader! msg: ") + msg
			+ "type: " + (type == GL_VERTEX_SHADER ? "vertex\n" : "fragment\n")).c_str());
		delete[] msg;

		glDeleteShader(id);
		return 0;
	}

	return id;
}
