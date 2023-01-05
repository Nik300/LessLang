#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __TYPEBASE_TYPE_HPP
#define __TYPEBASE_TYPE_HPP

#include <vector>
#include <string>
#include <stdint.h>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/runtime/variable.hpp>
#include <lesslang/types/typecheck/type_t.hpp>

namespace lesslang::types::typecheck
{
    typedef struct { bool success; runtime::variable result; } makeResult_t;
    /// @brief This is the base of any type
    struct typebase
    {
    private:
        type_t _spec;
    protected:
        inline typebase(type_t spec) :
            _spec(spec)
        {
        }
    public:
        inline type_t spec() const { return _spec; }
        virtual runtime::object * typeInfo() = 0;
        virtual uint32_t id() const = 0;
    public:
        /// @brief checks if the given value is an instance of this type
        /// @param value value to check
        /// @return true if it is, false if not
        virtual bool check(runtime::object *value, bool first = false) const = 0;
    public:
        /// @brief makes a new variable of this type with the given name
        /// @param name name of the declared variable
        /// @return struct that expresses if the variable was created correctly or not, and contains the created variable
        virtual makeResult_t make(std::string name) = 0;
        /// @brief makes a new variable of this type with the given name and generics
        /// @param name name of the declared variable
        /// @param generics generic signature of the type
        /// @return struct that expresses if the variable was created correctly or not, and contains the created variable
        virtual makeResult_t make(std::string name, std::vector<typebase *> generics) = 0;
    };
}

#endif