#include "pch.h"
#include "tag.h"

component::tag::tag(const std::string& tag_name) : m_tag(tag_name)
{
}

const std::string& component::tag::str() const
{
    return m_tag;
}

std::string& component::tag::str()
{
    return m_tag;
}
