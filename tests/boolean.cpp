#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/boolean.hpp>

int main()
{
    using namespace lesslang::types::runtime::primitives;
    using namespace lesslang::types::runtime;
    using namespace lesslang::types::typecheck;
    using namespace std;


    auto b1 = boolean_obj(true);
    auto b2 = boolean_obj(false);

    b1.applyOperator("&", b2.applyOperator("!", nullptr))->call(nullptr, vector<object *>());
    b1.applyOperator("|", &b2)->call(nullptr, vector<object *>());
}