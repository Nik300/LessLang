#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __GARBGECOLLECTOR_TYPE_HPP
#define __GARBGECOLLECTOR_TYPE_HPP

#include <string>
#include <vector>

#include <stddef.h>

#include <lesslang/types/runtime/scope.hpp>
#include <lesslang/types/runtime/object.hpp>

#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime
{
  class document;
  class garbageCollector final
  {
  friend class document;
  private:
    document *doc;
    std::vector<object *> allocation_table;
  public:
    inline garbageCollector(document *doc) :
      doc(doc)
    {
    }

    std::vector<object *> collect();
    void dispose(object *obj);
    void track(object *obj);
  };
}

#endif