#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __GARBGECOLLECTOR_TYPE_HPP
#define __GARBGECOLLECTOR_TYPE_HPP

#include <string>
#include <vector>

#include <stddef.h>

#include <lesslang/types/runtime/object.hpp>

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
    inline garbageCollector(garbageCollector const &) = delete;
    inline garbageCollector(garbageCollector &) = delete;

    std::vector<object *> collect();
    void dispose(object *obj) const;
    bool track(object *obj);

  public:
    inline void operator=(garbageCollector const &) = delete;
  };
}

#endif