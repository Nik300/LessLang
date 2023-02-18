#include <lesslang/tokenizer.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/dictionary.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>
#include <lesslang/types/runtime/primitives/number.hpp>
#include <lesslang/types/runtime/primitives/unsigned.hpp>
#include <lesslang/types/runtime/primitives/boolean.hpp>
#include <lesslang/types/runtime/primitives/union.hpp>
#include <lesslang/types/runtime/primitives/null.hpp>
#include <lesslang/types/runtime/primitives/function.hpp>

lesslang::types::runtime::object * test(lesslang::types::runtime::object *super, std::vector<lesslang::types::runtime::object *> args)
{
  if (args.size() == 1) printf("%s\n", args.at(0)->represent().c_str());
  return lesslang::types::runtime::primitives::null_obj::instance();
}

int main()
{
  using namespace lesslang::types::runtime::primitives;
  using namespace lesslang::types::runtime;
  using namespace lesslang::types::typecheck;
  using namespace std;

  builtin_function fn = builtin_function(test, nullptr);

  dict_obj obj = dict_obj({
    { "bool", new boolean_obj(true) },
    { "number", new number_obj(70) },
    { "unsigned", new unsigned_obj(0xDEADBEEF) },
    { "string", new string_obj("Hello, World!") },
    { "object", null_obj::instance() },
    { "builtin", &fn }
  });
  printf("%s\n", ((std::string)obj).c_str());
}