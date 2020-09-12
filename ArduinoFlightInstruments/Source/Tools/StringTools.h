#pragma once
#include <string>

namespace StringTools
{
    std::string ToString(std::wstring const& wstr);
    std::wstring ToWString(std::string const& str);
}
