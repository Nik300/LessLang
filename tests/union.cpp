#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>
#include <lesslang/types/runtime/primitives/number.hpp>
#include <lesslang/types/runtime/primitives/union.hpp>

int main()
{
    using namespace lesslang::types::runtime::primitives;
    using namespace lesslang::types::runtime;
    using namespace lesslang::types::typecheck;
    using namespace std;

    document main("main");

    auto scope = main.root()->createChild("test")->createChild("ok");
    bool r = scope->decGlobal("var", new primitives::union_type(vector<typebase*> {
        string_type::instance(),
        number_type::instance()
    }), new primitives::number_obj(10));
    main.get("test:ok:var")->call(nullptr, vector<object *>());

    main.set("test:ok:var", new string_obj("Hello World!"));
    main.get("test:ok:var")->call(nullptr, vector<object *>());
}