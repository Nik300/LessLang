#include <lesslang/types/runtime/primitives/union.hpp>
#include <lesslang.hpp>
#include <boost/foreach.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * union_type::typeInfo() { return nullptr; }
bool union_type::check(object *value, bool first) const
{
    auto *type = value->type();
#ifdef __USE_BOOST__
    BOOST_FOREACH(const auto& type, _types)
#else
    for (const auto& type : _types)
#endif
    {
        if (type->check(value, first)) return true;
    }
    return false;
}
uint32_t union_type::id() const { return UNION_TYPEID; }

makeResult_t union_type::make(std::string name) 
{
    return makeResult_t {
        .success = false
    };
}
makeResult_t union_type::make(std::string name, std::vector<typebase*>)
{
    return makeResult_t { .success = false, .result = variable(std::string(nullptr), nullptr) };
}
#pragma endregion