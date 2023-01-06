#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>
#include <lesslang/types/runtime/primitives/number.hpp>
#include <lesslang/types/runtime/primitives/boolean.hpp>
#include <lesslang/types/runtime/primitives/unsigned.hpp>
#include <lesslang/types/runtime/primitives/union.hpp>

int main()
{
    using namespace lesslang::types::runtime::primitives;
    using namespace lesslang::types::runtime;
    using namespace lesslang::types::typecheck;
    using namespace std;

    document main("main");

    auto scope = main.root();

    // var: "first" | "second" | 1 | 2 | 0x1 | 0x2 | false
    bool r = scope->decGlobal("var", new primitives::union_type(vector<typebase*> {
        new string_type("first"),
        new string_type("second"),
        new number_type(1),
        new number_type(2),
        new unsigned_type(0x1),
        new unsigned_type(0x2)
    }));
    
    main.set("var", new string_obj("first"));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new string_obj("second"));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new string_obj("blabla"));
    main.get("var")->call(nullptr, vector<object *> {});

    main.set("var", new number_obj(1));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new number_obj(2));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new number_obj(3));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new unsigned_obj(0x1));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new unsigned_obj(0x2));
    main.get("var")->call(nullptr, vector<object *> {});
    
    main.set("var", new unsigned_obj(0x3));
    main.get("var")->call(nullptr, vector<object *> {});
}