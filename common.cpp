#include "common.h"

std::vector<std::string> StrSplit(std::string_view str, std::string_view delimiters, bool skipEmptySubStr)
{
    std::vector<std::string> tokens;

    std::string::size_type pos = 0;
    std::string::size_type offset = 0;

    while (offset < str.length() + 1)
    {
        pos = str.find_first_of(delimiters, offset);
        if (pos == std::string::npos)
        {
            pos = str.length();
        }
        if (pos != offset || !skipEmptySubStr)
        {
            tokens.push_back(std::string(str.data() + offset, pos - offset));
        }
        offset = pos + 1;
    }

    return tokens;
}
