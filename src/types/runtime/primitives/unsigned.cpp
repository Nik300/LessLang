#include <lesslang/types/runtime/primitives/unsigned.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * unsigned_type::typeInfo() { return nullptr; }
bool unsigned_type::check(object *value, bool first) const
{
    auto *type = value->type();
    return
        type->spec() == type_t::TYPE && type->id() == UNSIGNED_TYPEID &&
        (!_content ? true : ((unsigned_obj*)value)->value() == _val);;
}
uint32_t unsigned_type::id() const { return UNSIGNED_TYPEID; }

makeResult_t unsigned_type::make(std::string name) 
{
    return makeResult_t {
        .success = true,
        .result = variable(name, this)
    };
}
makeResult_t unsigned_type::make(std::string name, std::vector<typebase*>)
{
    return makeResult_t { .success = false, .result = variable(std::string(nullptr), nullptr) };
}

unsigned_type *unsigned_type_inst = nullptr;
unsigned_type * unsigned_type::instance()
{
    if (unsigned_type_inst) return unsigned_type_inst;
    unsigned_type_inst = new unsigned_type();
    return unsigned_type_inst;
}
#pragma endregion

#pragma region OBJECT
unsigned_obj::unsigned_obj(uint64_t value) : object(unsigned_type::instance()), _value(value)
{
}
object * unsigned_obj::applyOperator(std::string op, object *right) const
{
    if (!unsigned_type::instance()->check(right)) return nullptr;
    unsigned_obj *other = (unsigned_obj *)right;

    if (op == "+" && other)
        return new unsigned_obj(_value + other->_value);
    else if (op == "-" && other)
        return new unsigned_obj(_value - other->_value);
    else if (op == "/" && other)
        return new unsigned_obj(_value / other->_value);
    else if (op == "*" && other)
        return new unsigned_obj(_value * other->_value);

    return nullptr;
}
object * unsigned_obj::get(std::string name) const
{
    printf("GET %s\n", name.c_str());
    return nullptr;
}
bool unsigned_obj::set(std::string name, object *value)
{
    printf("SET %s\n", name.c_str());
    return false;
}
object * unsigned_obj::call(object *super, std::vector<object *> args) const
{
    printf("%lX", _value);
    printf("\n");
    return nullptr;
}
std::vector<std::string> unsigned_obj::children() const
{
    return std::vector<std::string>();
}
#pragma endregion