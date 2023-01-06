#include <lesslang/types/runtime/primitives/union.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * union_type::typeInfo() { return nullptr; }
bool union_type::check(object *value, bool first) const
{
    auto *type = value->type();
    for (auto type : _types)
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