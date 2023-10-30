#pragma once
#include <string>

namespace component
{
	class tag
	{
	public:
		tag(const std::string& tag_name);
		const std::string& str() const;
	private:
		const std::string m_tag;
	};
}
