#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __UNSIGNED_RELEMENT_HPP
#define __UNSIGNED_RELEMENT_HPP

#define UNSIGNED_TYPEID 1

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
    struct unsigned_type final : typecheck::typebase
    {
    public:
        inline unsigned_type() : typebase(typecheck::type_t::TYPE)
        {
        }
    public:
        runtime::object * typeInfo() override;
        bool check(runtime::object *value, bool first = false) const override;
        uint32_t id() const override;
    public:
        typecheck::makeResult_t make(std::string name) override;
        typecheck::makeResult_t make(std::string name, std::vector<typecheck::typebase *> generics) override;
    public:
        static unsigned_type * instance();
    };

    class unsigned_obj final : public object
    {
    private:
        std::string _value;
    public:
        unsigned_obj(std::string value);
    public:
        object * applyOperator(std::string op, object *right) const override;
        object * get(std::string name) const override;
        bool set(std::string name, object *value) override;
        object * call(object *super, std::vector<object *> args) const override;
        std::vector<std::string> children() const override;
    public:
        inline std::string value() { return _value; }
    };
}

#endif