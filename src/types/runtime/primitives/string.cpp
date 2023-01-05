#include <lesslang/types/runtime/primitives/string.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * string_type::typeInfo() { return nullptr; }
bool string_type::check(object *value, bool first) const
{
    auto *type = value->type();
    return type->spec() == type_t::TYPE && type->id() == STRING_TYPEID;
}
uint32_t string_type::id() const { return STRING_TYPEID; }

makeResult_t string_type::make(std::string name) 
{
    return makeResult_t {
        .success = true,
        .result = variable(name, this)
    };
}
makeResult_t string_type::make(std::string name, std::vector<typebase*>)
{
    return makeResult_t { .success = false, .result = variable(std::string(nullptr), nullptr) };
}

string_type *string_type_inst = nullptr;
string_type * string_type::instance()
{
    if (string_type_inst) return string_type_inst;
    string_type_inst = new string_type();
    return string_type_inst;
}
#pragma endregion

#pragma region OBJECT
string_obj::string_obj(std::string value) : object(string_type::instance()), _value(value)
{
}
object * string_obj::applyOperator(std::string op, object *right) const
{
    if (!string_type::instance()->check(right)) return nullptr;
    string_obj *other = (string_obj *)right;

    if (op == "+")
        return new string_obj(_value + other->_value);
    
    return nullptr;
}
object * string_obj::get(std::string name) const
{
    printf("GET %s\n", name.c_str());
    return nullptr;
}
bool string_obj::set(std::string name, object *value)
{
    printf("SET %s\n", name.c_str());
    return false;
}
object * string_obj::call(object *super, std::vector<object *> args) const
{
    printf(_value.c_str());
    printf("\n");
    return nullptr;
}
std::vector<std::string> string_obj::children() const
{
    return std::vector<std::string>();
}
#pragma endregion