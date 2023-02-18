#include <lesslang.hpp>

#include <lesslang/types/runtime/garbagecollector.hpp>
#include <lesslang/types/runtime/document.hpp>
#include <lesslang/types/runtime/primitives/null.hpp>

#include <vector>
#include <string>

#include <boost/foreach.hpp>

using namespace std;
using namespace lesslang::types::runtime;
using namespace lesslang::types::runtime::primitives;

vector<object *> garbageCollector::collect() {
  vector<object *> unreferenced_table = vector<object *>();
  vector<object *> allocation_table_new = vector<object *>();

#ifdef __USE_BOOST__
  BOOST_FOREACH (const auto &obj, allocation_table)
#else
  for (const auto &obj : allocation_table)
#endif
  {
    auto locations = doc->locate(obj);

    if (locations.size() > 0) allocation_table_new.push_back(obj);
    else unreferenced_table.push_back(obj);
  }

  allocation_table = allocation_table_new;
  return unreferenced_table;
}
void garbageCollector::dispose(object *obj) const {
    auto locations = doc->locate(obj);
    if (locations.size() == 0) return;

#ifdef __USE_BOOST__
  BOOST_FOREACH (auto &var, locations)
#else
  for (auto &var : locations)
#endif
  {
    var.set(null_obj::instance());
  }
}
bool garbageCollector::track(object *obj) {
  allocation_table.push_back(obj);
  return true;
}