#include "StringTools.h"
#include <codecvt>

namespace StringTools
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // String conversion to/from wide string.
    // From https://riptutorial.com/cplusplus/example/4190/conversion-to-std--wstring
    using convert_t = std::codecvt_utf8<wchar_t>;

    std::string ToString(std::wstring const& wstr)
    {
        std::wstring_convert<convert_t, wchar_t> strconverter;
        return strconverter.to_bytes(wstr);
    }

    std::wstring ToWString(std::string const& str)
    {
        std::wstring_convert<convert_t, wchar_t> strconverter;
        return strconverter.from_bytes(str);
    }
}
