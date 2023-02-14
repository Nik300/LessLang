#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __VARIABLE_TYPE_HPP
#define __VARIABLE_TYPE_HPP

#include <string>
#include <lesslang/types/runtime/object.hpp>

namespace lesslang::types::typecheck
{
    struct typebase;
}
namespace lesslang::types::runtime
{
    struct variable final
    {
    friend class scope;
    friend class garbageCollector;
    private:
        std::string _name;
        typecheck::typebase *_type;
        object *_value;
    public:
        inline variable(std::string name, typecheck::typebase *type) :
            _name(name),
            _type(type)
        {
        }
        inline variable() :
            _name(),
            _type()
        {
        }
    public:
        inline const std::string & name() const { return _name; }
        inline const typecheck::typebase * type() const { return _type; }
    public:
        inline object * get() const { return _value; }
        inline void set(object *value) { _value = value; }
    public:
        inline const object * operator->() const
        {
            return _value;
        }
    };
}

#endif