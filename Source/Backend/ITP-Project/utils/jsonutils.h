#ifndef JSONUTILS_H
#define JSONUTILS_H

#include <string>
#include <sstream>
#include <map>
#include <variant> # std::get
#include <tuple> # std::get
#include <iostream> # std::cout

class JSONUtils
{
public:
    JSONUtils();
    using Value = std::variant<int, bool, std::string>;
    static std::string generateJSON(const std::map<std::string, Value>& data);
};

#endif // JSONUTILS_H
