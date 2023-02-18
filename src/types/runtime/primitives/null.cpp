#include <lesslang/types/runtime/primitives/null.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object *null_type::typeInfo()
{
  return nullptr;
}
bool null_type::check(object *value, bool first) const
{
  auto *type = value->type();
  return type->spec() == type_t::TYPE && type->id() == NULL_TYPEID;
}
uint32_t null_type::id() const { return NULL_TYPEID; }

makeResult_t null_type::make(std::string name)
{
  return makeResult_t{
      .success = true,
      .result = variable(name, this)};
}
makeResult_t null_type::make(std::string name, std::vector<typebase *>)
{
  return makeResult_t{.success = false, .result = variable(std::string(nullptr), nullptr)};
}

null_type *null_type_inst = nullptr;
null_type *null_type::instance()
{
  if (null_type_inst)
    return null_type_inst;
  null_type_inst = new null_type();
  return null_type_inst;
}
#pragma endregion

#pragma region OBJECT
null_obj::null_obj() : object(null_type::instance())
{
}
object *null_obj::applyOperator(std::string op, object *right) const
{
  return null_obj::instance();
}
object *null_obj::get(std::string name) const
{
  printf("GET %s\n", name.c_str());
  return nullptr;
}
bool null_obj::set(std::string name, object *value)
{
  printf("SET %s\n", name.c_str());
  return false;
}
object *null_obj::call(object *super, std::vector<object *> args) const
{
  return nullptr;
}
std::vector<std::string> null_obj::children() const
{
  return std::vector<std::string>();
}
std::string null_obj::represent() const
{
  return "\033[1;34mnull\033[0;m";
}
null_obj * null_obj::instance()
{
  static null_obj * result = nullptr;
  if (result != nullptr) return result;
  return result = new null_obj;
}
#pragma endregion