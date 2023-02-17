#include <lesslang/types/runtime/document.hpp>
#include <lesslang.hpp>

#include <lesslang/types/runtime/primitives/boolean.hpp>
#include <lesslang/types/runtime/primitives/number.hpp>
#include <lesslang/types/runtime/primitives/unsigned.hpp>
#include <lesslang/types/runtime/primitives/null.hpp>

#include <tuple>
#include <boost/foreach.hpp>

using namespace std;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

static bool isnumber(string str)
{
#ifdef __USE_BOOST__
  BOOST_FOREACH (const char &c, str)
#else
  for (const char &c : str)
#endif
  {
    if (!std::isdigit(c))
      return false;
  }
  return true;
}
static bool ishex(string str)
{
  if (str.find("0x") != 0 && str.find("0X"))
    return false;

  string expr = str.substr(2);

#ifdef __USE_BOOST__
  BOOST_FOREACH (const char &c, expr)
#else
  for (const char &c : expr)
#endif
  {
    if ((c < '0' || c > '9') && (c < 'A' || c > 'F') && (c < 'a' || c > 'f'))
      return false;
  }
  return true;
}

tuple<scope *, string> access_scope(scope *root, string id)
{
  scope *curr = root;

  size_t x = 0;
  size_t c = 0;
  while ((c = id.find(':', x)) != -1)
  {
    auto rid = id.substr(x, c - x);
    curr = curr->getChild(rid);
    if (curr == nullptr)
      return {nullptr, string()};
    x = c + 1;
  }

  return {curr, id.substr(x)};
}
object * get_object_property(scope *root, string id)
{
  object *curr = nullptr;

  size_t x = 0;
  size_t c = 0;
  while ((c = id.find('.', x)) != -1)
  {
    auto rid = id.substr(x, c - x);

    if (!curr)
      curr = root->getGlobal(rid);
    else
      curr = curr->get(rid);

    if (curr == nullptr)
      return nullptr;
    x = c + 1;
  }

  if (!curr)
    return root->getGlobal(id);
  else
    return curr->get(id.substr(x));
}
bool set_object_property(scope *root, string id, object *value)
{
  object *curr = nullptr;
  typebase *type = nullptr;

  size_t x = 0;
  size_t c = 0;
  while ((c = id.find('.', x)) != -1)
  {
    auto rid = id.substr(x, c - x);

    if (!curr)
      curr = root->getGlobal(rid);
    else
      curr = curr->get(rid);

    if (curr == nullptr)
      return false;
    x = c + 1;
  }

  if (!curr)
    return root->setGlobal(id, value);
  else
    return curr->set(id.substr(x), value);
}

std::vector<variable> document::inspect_scope(std::vector<variable> trace, const scope &at, object *obj)
{
  bool  globalExec = true,
        localExec = true;

  for (
    auto  globalIterator = at._globals.begin(),
          localIterator =  at._locals.begin();
    globalExec || localExec;
  ) {
    if (globalExec && globalIterator == at._globals.end())
      globalExec = false;
    if (localExec && localIterator == at._locals.end())
      localExec = false;

    if (!globalExec) goto localCheck;
    if (globalIterator->second.get() == obj)
      trace.push_back(globalIterator->second);

    localCheck:
    if (!localExec) goto for_gl_end;
    if (localIterator->second.get() == obj)
      trace.push_back(localIterator->second);

    for_gl_end:
    if (globalExec) globalIterator++;
    if (localExec)  localIterator++;
  }

#ifdef __USE_BOOST__
  BOOST_FOREACH (const auto &child, at._children)
#else
  for (const auto &child : at._children)
#endif
  {
    inspect_scope(
      trace,
      child.second,
      obj
    );
  }

  return trace;
}

std::vector<variable> document::locate(object *obj) { return inspect_scope(std::vector<variable>(), this->_root, obj); }

typebase * document::type(string id)
{
  auto [scope, name] = access_scope(&_root, id);

  if (!scope)
    return nullptr;
  return scope->getType(name);
}

const variable document::var(string id)
{
  auto [scope, varname] = access_scope(&_root, id);

  if (!scope || !scope->_globals.count(varname))
    return variable();
  return scope->_globals[varname];
}

object * document::get(string id)
{
  auto [scope, varname] = access_scope(&_root, id);

  if (!scope)
    return nullptr;

  return get_object_property(scope, varname);
}
bool document::set(string id, object *value)
{
  auto [scope, varname] = access_scope(&_root, id);

  if (!scope)
    return false;

  return set_object_property(scope, varname, value);
}

scope * document::root() { return &_root; }
scope * document::resolve(string id)
{
  auto [scope, _] = access_scope(&_root, id);
  return scope;
}

bool document::import(document *doc)
{
  if (_root._children.count(doc->_root._name))
    return false;

  _root._children[doc->_root._name] = doc->_root;
  return true;
}
bool document::import(document *doc, string as)
{
  if (_root._children.count(as))
    return false;

  _root._children[as] = doc->_root;
  return true;
}

object * document::eval(string expr)
{
  using namespace lesslang::types::runtime::primitives;
  if (strcmp(expr.c_str(), "null") == 0 || strcmp(expr.c_str(), "undefined") == 0)
    return null_obj::instance();

  if (isnumber(expr))
    return new number_obj(std::stoll(expr));
  else if (ishex(expr))
    return new unsigned_obj(std::stoull(expr.substr(2), 0, 16));

  if (strcmp(expr.c_str(), "true") == 0)
    return new boolean_obj(true);
  else if (strcmp(expr.c_str(), "false") == 0)
    return new boolean_obj(false);

  return new string_obj(expr);
}