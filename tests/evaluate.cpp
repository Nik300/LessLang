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

int main()
{
  using namespace lesslang::types::runtime::primitives;
  using namespace lesslang::types::runtime;
  using namespace lesslang::types::typecheck;
  using namespace std;

  document main("main");

  object* obj = main.eval("\rCiao!\b\\");
  printf("%s\n", obj->represent().c_str());
}