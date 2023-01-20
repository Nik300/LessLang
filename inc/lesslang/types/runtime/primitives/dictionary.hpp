#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __DICT_RELEMENT_HPP
#define __DICT_RELEMENT_HPP

#define DICT_TYPEID 6

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime::primitives
{
    struct dict_type final : typecheck::typebase
    {
    friend class dict_obj;
    public:
        typedef std::map<std::string, typecheck::typebase *> dictType_t;
    private:
        dictType_t _typeMap;
    public:
        inline dict_type(dictType_t typeMap) :
            typebase(typecheck::type_t::TYPE),
            _typeMap(typeMap)
        {
        }
        inline dict_type() :
            typebase(typecheck::type_t::TYPE),
            _typeMap({})
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
        static dict_type * instance();
    };

    class dict_obj final : public object
    {
    public:
        typedef std::map<std::string, object *> dictValue_t;
    private:
        dictValue_t _value;
    public:
        dict_obj(dictValue_t value);
    public:
        object * applyOperator(std::string op, object *right) const override;
        object * get(std::string name) const override;
        bool set(std::string name, object *value) override;
        object * call(object *super, std::vector<object *> args) const override;
        std::vector<std::string> children() const override;
    public:
        inline dictValue_t value() { return _value; }
    };
}

#endif