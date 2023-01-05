#include <lesslang/types/runtime/object.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

const typebase * object::type() const {
    return this->_type;
}
object * object::get(std::string) const { return nullptr; } 
bool object::set(std::string, object *) { return false; }