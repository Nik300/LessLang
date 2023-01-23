#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __STRING_RELEMENT_HPP
#define __STRING_RELEMENT_HPP

#define STRING_TYPEID 1

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
    struct string_type final : typecheck::typebase
    {
    private:
        bool _content;
        std::string _val;
    public:
        inline string_type() :
            typebase(typecheck::type_t::TYPE),
            _val(),
            _content(false)
        {
        }
        inline string_type(std::string value) :
            typebase(typecheck::type_t::TYPE),
            _val(value),
            _content(true)
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
        static string_type * instance();
    };

    class string_obj final : public object
    {
    private:
        std::string _value;
    public:
        string_obj(std::string value);
    public:
        object * applyOperator(std::string op, object *right) const override;
        object * get(std::string name) const override;
        bool set(std::string name, object *value) override;
        object * call(object *super, std::vector<object *> args) const override;
        std::vector<std::string> children() const override;
        std::string represent() const override;
    public:
        inline std::string value() { return _value; }
    };
}

#endif