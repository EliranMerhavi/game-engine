#pragma once
#include <string>

namespace component
{
	class tag
	{
	public:
		tag() = default;
		tag(const std::string& tag_name);

		const std::string& str() const;
		std::string& str();
	private:
		std::string m_tag;
	};
}
