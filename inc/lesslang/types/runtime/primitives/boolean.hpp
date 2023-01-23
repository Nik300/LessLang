#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __BOOLEAN_RELEMENT_HPP
#define __BOOLEAN_RELEMENT_HPP

#define BOOLEAN_TYPEID 4

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
    struct boolean_type final : typecheck::typebase
    {
    private:
        bool _content;
        bool _val;
    public:
        inline boolean_type() :
            typebase(typecheck::type_t::TYPE),
            _content(false),
            _val()
        {
        }
        inline boolean_type(bool value) :
            typebase(typecheck::type_t::TYPE),
            _content(true),
            _val(value)
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
        static boolean_type * instance();
    };

    class boolean_obj final : public object
    {
    private:
        bool _value;
    public:
        boolean_obj(bool value);
    public:
        object * applyOperator(std::string op, object *right) const override;
        object * get(std::string name) const override;
        bool set(std::string name, object *value) override;
        object * call(object *super, std::vector<object *> args) const override;
        std::string represent() const override;
        std::vector<std::string> children() const override;
    public:
        inline bool value() { return _value; }
    };
}

#endif