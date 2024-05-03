#pragma once


struct load_args_t
{
	std::string filepath;
	const void* file_data;
	size_t length;
};

class resource_t
{
public:
	virtual void load(const load_args_t& args) = 0;
};