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

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;
using namespace std;

void test1(document &doc) {
  printf("Test 1 ... ");
  auto collected = doc.collector().collect();
  if (collected.size() == 0) printf("✅ Passed!\n");
  else printf("❌ Not passed!\n");
}
void test2(document &doc) {
  printf("Test 2 ... ");
  auto collected = doc.collector().collect();
  if (collected.size() == 1) printf("✅ Passed!\n");
  else printf("❌ Not passed!\n");
}
void test3(document &doc) {
  printf("Test 3 ... ");
  auto collected = doc.collector().collect();
  if (collected.size() == 0) printf("✅ Passed!\n");
  else printf("❌ Not passed!\n");
}

void prepare_test1(document &doc) {
  bool a = doc.declare(variable_type::GLOBAL, "test", new union_type({
    string_type::instance(),
    null_type::instance()
  }), new string_obj("Hello"));
}
void prepare_test2(document &doc) {
  doc.set("test", null_obj::instance());
}

int main()
{
  document main("main");

  prepare_test1(main);
  test1(main);

  prepare_test2(main);
  test2(main);

  test3(main);
}