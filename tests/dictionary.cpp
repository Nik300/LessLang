#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/dictionary.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>
#include <lesslang/types/runtime/primitives/number.hpp>

int main()
{
    using namespace lesslang::types::runtime::primitives;
    using namespace lesslang::types::runtime;
    using namespace lesslang::types::typecheck;
    using namespace std;

    document main("main");

    dict_type t = dict_type((dict_type::dictType_t) {
        { "str", string_type::instance() },
        { "num", number_type::instance() }
    });
    dict_obj o = dict_obj((dict_obj::dictValue_t) {
        { "str", new string_obj("Hello, World!") },
        { "num", new number_obj(1) }
    });
    main.root()->decGlobal("test", &t, &o);

    main.get("test")->get("num")->call(nullptr, vector<object *> {});

    main.get("test")->set("num", new number_obj(2));
    main.get("test")->get("num")->call(nullptr, vector<object *> {});
}