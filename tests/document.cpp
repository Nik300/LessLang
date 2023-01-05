#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>

int main()
{
    using namespace lesslang::types::runtime;
    using namespace std;

    document doc("main");

    auto scope = doc.root()->createChild("test")->createChild("ok");
    bool r = scope->decGlobal("var", primitives::string_type::instance(), new primitives::string_obj("Hello, Runtime!"));

    
}