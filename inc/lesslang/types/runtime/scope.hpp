#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __SCOPE_TYPE_HPP
#define __SCOPE_TYPE_HPP

#include <vector>
#include <map>
#include <string>
#include <lesslang/types/runtime/variable.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime
{
  class scope final
  {
    friend class document;

  private:
    std::map<std::string, variable> _locals;
    std::map<std::string, variable> _globals;
    std::map<std::string, scope> _children;
    std::string _name;
    std::map<std::string, typecheck::typebase *> _types;
    scope *_parent;
    inline scope(std::string name, scope *parent) :
      _locals(),
      _globals(),
      _types(),
      _children(),
      _name(name),
      _parent(parent)
    {
    }

  public:
    const std::string &name();
    scope *createChild(std::string name);
    scope *getChild(std::string name);

  public:
    object *getLocal(std::string local);
    object *getGlobal(std::string global);
    typecheck::typebase *getType(std::string name);

    bool setLocal(std::string local, object *value);
    bool setGlobal(std::string global, object *value);

    bool decLocal(std::string name, typecheck::typebase *type, object *value = nullptr);
    bool decGlobal(std::string name, typecheck::typebase *type, object *value = nullptr);
    bool decType(std::string name, typecheck::typebase *type);
    inline ~scope()
    {
      _locals.clear();
      _globals.clear();
      _name.~basic_string();
    }
    inline scope() : _locals(),
                     _globals(),
                     _types(),
                     _children(),
                     _name(),
                     _parent(nullptr)
    {
    }
  };
}

#endif