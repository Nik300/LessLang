#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>

int main()
{
    using namespace lesslang::types::runtime;
    using namespace std;

    document fw("fw");
    document main("main");

    auto scope = fw.root()->createChild("test")->createChild("ok");
    bool r = scope->decGlobal("var", primitives::string_type::instance(), new primitives::string_obj("Hello, Runtime!"));

    main.import(&fw);

    main.var("fw:test:ok:var")->call(nullptr, vector<object *>());
}