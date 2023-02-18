#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __DOCUMENT_TYPE_HPP
#define __DOCUMENT_TYPE_HPP

#include <string>
#include <vector>
#include <stddef.h>

#include <lesslang/types/runtime/scope.hpp>
#include <lesslang/types/runtime/object.hpp>
#include <lesslang/types/runtime/garbagecollector.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime
{
  class document final
  {
  friend class garbageCollector;
  private:
    scope _root;
    std::string _name;
    garbageCollector _collector;
  private:
    std::vector<variable> inspect_scope(std::vector<variable> trace, const scope &at, object *obj);

  public:
    std::vector<variable> locate(object *obj);

    typecheck::typebase *type(std::string id);

    const variable var(std::string id);

    object * get(std::string id);
    bool set(std::string id, object *value);
    bool declare(variable_type var_type, std::string name, typecheck::typebase *type, object *value = nullptr);

    scope * root();
    scope * resolve(std::string id);

    bool import(document *doc);
    bool import(document *doc, std::string as);

    object * eval(std::string expr);

    inline document(std::string name) :
      _root(name, nullptr),
      _name(name),
      _collector(this)
    {
    }

  public:
    inline garbageCollector & collector() { return _collector; }
  };
}

#endif