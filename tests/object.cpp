#include <stdio.h>
#include <memory>
#include <lesslang.hpp>

int main()
{
    using namespace lesslang::types::runtime;
    using namespace lesslang::types::runtime::primitives;

    object *test = (object *)new string_obj("Hello World!");
    object *res = test->applyOperator("+", (object *)new string_obj(" OK"));

    res->call(nullptr, std::vector<object *>());

    return 0;
}