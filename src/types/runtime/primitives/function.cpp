#include <lesslang/types/runtime/primitives/function.hpp>
#include <lesslang.hpp>

#include <boost/foreach.hpp>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::typecheck;
using namespace lesslang::types::runtime;

#pragma region FUNCTION_TYPE
bool function_type::check(runtime::object *value, bool first) const {
  const function_type *type = (const function_type *)value->type();
  if (type->id() != FUNCTION_TYPEID || this->_return_type != type->_return_type) return false;

  for (
    auto it = _params_types.begin(), cit = type->_params_types.begin();
    it != _params_types.end() && cit != this->_params_types.end();
    it++, cit++
  ) {
    if (*it != *cit) return false;
  }

  return _params_types.size() == type->_params_types.size();
}

uint32_t function_type::id() const { return FUNCTION_TYPEID; }
#pragma endregion

#pragma region FUNCTION_OBJECTS
builtin_function::builtin_function(object * (*function)(object *super, std::vector<object *> args), function_type *type) : object(type),
  _fn(function)
{
}
object * builtin_function::call(object *super, std::vector<object *> args) const { return _fn(super, args); }
object * builtin_function::applyOperator(std::string op, object *right) const { return nullptr; }
std::vector<std::string> builtin_function::children() const { return std::vector<std::string>(); }
std::string builtin_function::represent() const {
  return "\033[1;96m[builtin function]\033[0;m";
}
object * builtin_function::get(std::string name) const { return nullptr; }
bool builtin_function::set(std::string name, object *value) { return false; }
#pragma endregion