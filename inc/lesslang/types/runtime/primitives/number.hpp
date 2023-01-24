#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __NUMBER_RELEMENT_HPP
#define __NUMBER_RELEMENT_HPP

#define NUMBER_TYPEID 2

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
    struct number_type final : typecheck::typebase
    {
    private:
        bool _content;
        int64_t _val;
    public:
        inline number_type() :
            typebase(typecheck::type_t::TYPE),
            _content(false),
            _val()
        {
        }
        inline number_type(int64_t value) :
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
        static number_type * instance();
    };

    class number_obj final : public object
    {
    private:
        int64_t _value;
    public:
        number_obj(int64_t value);
    public:
        object * applyOperator(std::string op, object *right) const override;
        object * get(std::string name) const override;
        bool set(std::string name, object *value) override;
        object * call(object *super, std::vector<object *> args) const override;
        std::string represent() const override;
        std::vector<std::string> children() const override;
    public:
        inline int64_t value() { return _value; }
    };
}

#endif