#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __FRAMEWORK_TYPE_HPP
#define __FRAMEWORK_TYPE_HPP

#include <vector>
#include <string>
#include <tuple>
#include <stdint.h>

#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types
{
    struct framework
    {
    private:
        std::string _name;
    protected:
        inline framework(std::string name) :
            _name(name)
        {
        }
    public:
        virtual typecheck::typebase *evalType(std::string expr) = 0;
        virtual runtime::object *eval(std::string expr) = 0;
        virtual bool collect() = 0;
        virtual size_t usage() = 0;
        virtual void yield() = 0;
    };
}

#endif