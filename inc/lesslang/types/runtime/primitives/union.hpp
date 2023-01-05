#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __UNION_RELEMENT_HPP
#define __UNION_RELEMENT_HPP

#define UNION_TYPEID 0xFFFF0001

#include <stdint.h>
#include <string>
#include <vector>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
    struct union_type final : typecheck::typebase
    {
    private:
        std::vector<typecheck::typebase *> _types;
    public:
        inline union_type(std::vector<typecheck::typebase *> types) :
            typebase(typecheck::type_t::TYPE_EXPR),
            _types(types)
        {
        }
    public:
        runtime::object * typeInfo() override;
        bool check(runtime::object *value, bool first = false) const override;
        uint32_t id() const override;
    public:
        typecheck::makeResult_t make(std::string name) override;
        typecheck::makeResult_t make(std::string name, std::vector<typecheck::typebase *> generics) override;
    };
}

#endif