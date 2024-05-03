#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include <unordered_map>
#include "resource_t.h"

class resource_system_t
{
public:
	using resource_holder_t = std::pair<size_t, resource_t*>;
public:
	resource_system_t();
	~resource_system_t();

	void add_search_path(const std::string& path);

	template<typename t, typename... args_t>
	void load(const std::string& filename, args_t... args)
	{
		std::string path = fullpath(filename);

		assert(path.size() && "file not found");
		assert(!has(filename) && "resource already exists");

		resource_t* resource = new t(std::forward<args_t>(args)...);
		size_t file_size;
		void* data = load_file_data(path, file_size);
		
		resource->load({ path, data, file_size });
		delete[] data;

		m_resources[filename] = { typeid(t).hash_code(), resource };
	}

	template<typename t>
	t& get(const std::string& filename)
	{
		assert(has(filename) && "resource not found");
		
		auto& [hash_code, data] = m_resources.at(filename);
		
		assert(typeid(t).hash_code() == hash_code && "type mismatch");
	
		return *(t*)data;
	}

	bool has(const std::string& filename) const;

	void close(const std::string& filename);
private:
	std::string fullpath(const std::string& filename) const;
	void* load_file_data(const std::string& filepath, size_t& length) const;

	std::vector<std::string> m_filepaths;
	std::unordered_map<std::string, resource_holder_t> m_resources;
};