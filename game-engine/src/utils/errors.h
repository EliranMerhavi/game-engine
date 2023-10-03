#pragma once

#define assert(condition, message) if (!(condition)) throw std::exception((message).c_str());
namespace errors
{
	enum class library_enum
	{
		GLEW,
		GLFW
	};

	class library_init_error : public std::exception
	{
	public:
		library_init_error(library_enum library, const std::string& message);
		library_enum which_library() const;
	private:
		library_enum m_library;
	};
}
