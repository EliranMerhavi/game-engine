#include "pch.h"
#include "errors.h"



errors::library_init_error::library_init_error(library_enum library,const std::string& message) :
	std::exception(message.c_str()), m_library(library)
{
}

errors::library_enum errors::library_init_error::which_library() const
{
	return m_library;
}