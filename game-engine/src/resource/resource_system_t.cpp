#include "pch.h"
#include "resource_system_t.h"
#include <filesystem>

resource_system_t::resource_system_t()
	: m_filepaths(), m_resources()
{
}

resource_system_t::~resource_system_t()
{
	for (const auto& [filepath, resource_holder] : m_resources) {
		delete resource_holder.second;
	}
}

void resource_system_t::add_search_path(const std::string& path)
{
	m_filepaths.emplace_back(path);
}

bool resource_system_t::has(const std::string& filename) const
{
	return m_resources.count(filename);
}

void resource_system_t::close(const std::string& filename)
{
	assert(m_resources.count(filename) && "resource not found");
	delete m_resources.at(filename).second;
	m_resources.erase(filename);
}

std::string resource_system_t::fullpath(const std::string& filename) const
{
    for (const auto& path : m_filepaths) {
        std::string filepath = path + filename;
        if (std::filesystem::exists(filepath)) {
            return filepath;
        }
    }
    return "";
}

void* resource_system_t::load_file_data(const std::string& filepath, size_t& length) const
{
	FILE* fp;
	
	assert(!fopen_s(&fp, filepath.c_str(), "rb") && "could not open the file");

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	rewind(fp);
	char* buff = new char[length];
	fread(buff, sizeof(char), length, fp);
	fclose(fp);

	return buff;
}
