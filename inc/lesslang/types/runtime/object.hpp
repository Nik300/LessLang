#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __OBJECT_TYPE_HPP
#define __OBJECT_TYPE_HPP

#include <string>
#include <vector>

namespace lesslang::types::typecheck
{
    class typebase;
}
namespace lesslang::types::runtime
{
    class object
    {
    friend class scope;
    protected:
        typecheck::typebase *_type;
    public:
        /// @brief applies an operator to the object
        /// @param op operator to apply
        /// @param right right operand
        /// @return new object with applied operator
        virtual object * applyOperator(std::string op, object *right) const = 0;
        /// @brief get property of element
        /// @param name name of the child to return
        /// @return object child
        virtual object * get(std::string name) const;
        /// @brief set property of element
        /// @param name name of the property
        /// @param value value to set
        /// @return object child
        virtual bool set(std::string name, object *value);
        virtual inline bool set(typecheck::typebase *superType, std::string name, object *value) {
            return set(name, value);
        }
        /// @brief calls the object
        /// @param super value of 'this' 
        /// @param args arguments to call the object with
        /// @return return value of the call
        virtual object * call(object *super, std::vector<object *> args) const = 0;
        /// @brief get a list of this object's children names
        /// @return object's children names
        virtual std::vector<std::string> children() const = 0;
        const typecheck::typebase * type() const;
    private:
        bool mutate(const typecheck::typebase *type);
    protected:
        inline object(typecheck::typebase *type) :
            _type(type)
        {
        }
    };
}

#endif