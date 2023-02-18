#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __FUNCTION_RELEMENT_HPP
#define __FUNCTION_RELEMENT_HPP

#define FUNCTION_TYPEID 7

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
  struct function_type final : typecheck::typebase
  {
  private:
    std::vector<typecheck::typebase *> _params_types;
    typecheck::typebase *_return_type;

  public:
    inline function_type(typecheck::typebase *return_type) : typebase(typecheck::type_t::TYPE),
      _params_types(),
      _return_type(return_type)
    {
    }
    inline function_type(std::vector<typecheck::typebase *> parameters, typecheck::typebase *return_type) : typebase(typecheck::type_t::TYPE),
      _params_types(parameters),
      _return_type(return_type)
    {
    }

  public:
    runtime::object *typeInfo() override;
    bool check(runtime::object *value, bool first = false) const override;
    uint32_t id() const override;

  public:
    typecheck::makeResult_t make(std::string name) override;
    typecheck::makeResult_t make(std::string name, std::vector<typecheck::typebase *> generics) override;

  public:
    const typecheck::typebase & return_type() { return *_return_type; }
  };

  class builtin_function final : public object
  {
  private:
    object * (*_fn)(object *super, std::vector<object *> args);

  public:
    builtin_function(object * (*function)(object *super, std::vector<object *> args), function_type *type);

  public:
    object *applyOperator(std::string op, object *right) const override;
    object *get(std::string name) const override;
    bool set(std::string name, object *value) override;
    object *call(object *super, std::vector<object *> args) const override;
    std::vector<std::string> children() const override;
    std::string represent() const override;
  };
}

#endif