#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __NULL_RELEMENT_HPP
#define __NULL_RELEMENT_HPP

#define NULL_TYPEID 5

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
  struct null_type final : typecheck::typebase
  {
  private:
    bool _content;
    std::string _val;

  public:
    inline null_type() : typebase(typecheck::type_t::TYPE),
      _val(),
      _content(false)
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
    static null_type *instance();
  };

  class null_obj final : public object
  {
  private:
    null_obj();

  public:
    object *applyOperator(std::string op, object *right) const override;
    object *get(std::string name) const override;
    bool set(std::string name, object *value) override;
    object *call(object *super, std::vector<object *> args) const override;
    std::vector<std::string> children() const override;
    std::string represent() const override;

  public:
    static null_obj * instance(); 
  };
}

#endif