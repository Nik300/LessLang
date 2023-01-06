#include <lesslang/types/runtime/primitives/number.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * number_type::typeInfo() { return nullptr; }
bool number_type::check(object *value, bool first) const
{
    auto *type = value->type();
    return
        type->spec() == type_t::TYPE && type->id() == NUMBER_TYPEID &&
        (!_content ? true : ((number_obj *)value)->value() == _val);
}
uint32_t number_type::id() const { return NUMBER_TYPEID; }

makeResult_t number_type::make(std::string name) 
{
    return makeResult_t {
        .success = true,
        .result = variable(name, this)
    };
}
makeResult_t number_type::make(std::string name, std::vector<typebase*>)
{
    return makeResult_t { .success = false, .result = variable(std::string(nullptr), nullptr) };
}

number_type *number_type_inst = nullptr;
number_type * number_type::instance()
{
    if (number_type_inst) return number_type_inst;
    number_type_inst = new number_type();
    return number_type_inst;
}
#pragma endregion

#pragma region OBJECT
number_obj::number_obj(int64_t value) : object(number_type::instance()), _value(value)
{
}
object * number_obj::applyOperator(std::string op, object *right) const
{
    if (!number_type::instance()->check(right)) return nullptr;
    number_obj *other = (number_obj *)right;

    if (op == "+" && other)
        return new number_obj(_value + other->_value);
    else if (op == "-" && other)
        return new number_obj(_value - other->_value);
    else if (op == "/" && other)
        return new number_obj(_value / other->_value);
    else if (op == "*" && other)
        return new number_obj(_value * other->_value);
    
    return nullptr;
}
object * number_obj::get(std::string name) const
{
    printf("GET %s\n", name.c_str());
    return nullptr;
}
bool number_obj::set(std::string name, object *value)
{
    printf("SET %s\n", name.c_str());
    return false;
}
object * number_obj::call(object *super, std::vector<object *> args) const
{
    printf("%ld", _value);
    printf("\n");
    return nullptr;
}
std::vector<std::string> number_obj::children() const
{
    return std::vector<std::string>();
}
#pragma endregion