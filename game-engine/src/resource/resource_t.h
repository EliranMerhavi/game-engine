#pragma once

class resource_t
{
public:
	virtual void load(const void* file_data, size_t length) = 0;
};