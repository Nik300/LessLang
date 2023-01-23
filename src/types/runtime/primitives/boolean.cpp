#include <lesslang/types/runtime/primitives/boolean.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * boolean_type::typeInfo() { return nullptr; }
bool boolean_type::check(object *value, bool first) const
{
    auto *type = value->type();
    return
        type->spec() == type_t::TYPE && type->id() == BOOLEAN_TYPEID &&
        (!_content ? true : ((boolean_obj *)value)->value() == _val);
}
uint32_t boolean_type::id() const { return BOOLEAN_TYPEID; }

makeResult_t boolean_type::make(std::string name) 
{
    return makeResult_t {
        .success = true,
        .result = variable(name, this)
    };
}
makeResult_t boolean_type::make(std::string name, std::vector<typebase*>)
{
    return makeResult_t { .success = false, .result = variable(std::string(nullptr), nullptr) };
}

boolean_type *boolean_type_inst = nullptr;
boolean_type * boolean_type::instance()
{
    if (boolean_type_inst) return boolean_type_inst;
    boolean_type_inst = new boolean_type();
    return boolean_type_inst;
}
#pragma endregion

#pragma region OBJECT
boolean_obj::boolean_obj(bool value) : object(boolean_type::instance()), _value(value)
{
}
object * boolean_obj::applyOperator(std::string op, object *right) const
{
    boolean_obj *other = (boolean_obj *)right;

    if (op == "!" && !other)
        return new boolean_obj(!_value);

    if (!boolean_type::instance()->check(right)) return nullptr;

    if (op == "==" && other)
        return new boolean_obj(_value == other->_value);
    else if (op == "!=" && other)
        return new boolean_obj(_value != other->_value);
    else if (op == "|" && other)
        return new boolean_obj(_value || other->_value);
    else if (op == "&" && other)
        return new boolean_obj(_value && other->_value);
    
    return nullptr;
}
object * boolean_obj::get(std::string name) const
{
    return nullptr;
}
bool boolean_obj::set(std::string name, object *value)
{
    return false;
}
object * boolean_obj::call(object *super, std::vector<object *> args) const
{
    return nullptr;
}
std::string boolean_obj::represent() const 
{
    return _value ? "True" : "False";
}
std::vector<std::string> boolean_obj::children() const
{
    return std::vector<std::string>();
}
#pragma endregion