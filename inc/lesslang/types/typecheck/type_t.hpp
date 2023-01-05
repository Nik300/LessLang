#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __TYPE_ENUM_HPP
#define __TYPE_ENUM_HPP

#include <string>
#include <stdint.h>
#include <lesslang/types/runtime/object.hpp>

namespace lesslang::types::typecheck
{
    enum class type_t : uint8_t
    {
        TYPE,
        TYPE_EXPR
    };
}

#endif