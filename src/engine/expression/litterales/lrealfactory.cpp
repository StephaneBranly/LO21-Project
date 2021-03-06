#include "lrealfactory.h"
#include <regex>
#include "lreal.h"

// Reconnaissance des Lreal
bool Engine::LrealFactory::isSameType(const std::string s) const
{
    std::regex str_expr1("[0-9]*\\.[0-9]+");
    std::regex str_expr2("[0-9]+\\.[0-9]*");
    return (regex_match(s,str_expr1) || regex_match(s,str_expr2));
}
Engine::Lreal* Engine::LrealFactory::createExpressionFromString(const std::string s) const
{
    return new Lreal(s);
}
