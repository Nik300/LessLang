#include <lesslang/types/runtime/scope.hpp>

using namespace std;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

const string & scope::name() { return this->_name; }

scope * scope::createChild(string name)
{
    scope result = scope(name, this);
    _children[name] = scope(name, this);
    return &(_children[name]);
}
scope * scope::getChild(string name)
{
    if (!_children.count(name)) return nullptr;
    return &(_children[name]);
}

object * scope::getLocal(string name)
{
    if (!_locals.count(name)) return nullptr;
    return _locals[name].get();
}
object * scope::getGlobal(string name)
{
    if (!_globals.count(name)) return nullptr;
    return _globals[name].get();
}
typebase * scope::getType(string name)
{
    if (!_types.count(name)) return nullptr;
    return _types[name];
}

bool scope::setLocal(string name, object *value)
{
    if (!_locals.count(name) || !value->mutate(_locals[name].type())) return false;
    _locals[name].set(value);
    return true;
}
bool scope::setGlobal(string name, object *value)
{
    if (!_globals.count(name) || !value->mutate(_globals[name].type())) return false;
    _globals[name].set(value);
    return true;
}

bool scope::decLocal(string name, typebase *type, object *value)
{
    if (_locals.count(name)) return false;
    auto var = _locals[name] = variable(name, type);
    if (value && value->mutate(var.type())) _locals[name].set(value);
    return true;
}
bool scope::decGlobal(string name, typebase *type, object *value)
{
    if (_globals.count(name)) return false;
    auto var = _globals[name] = variable(name, type);
    if (value && value->mutate(var.type())) _globals[name].set(value);
    return true;
}
bool scope::decType(string name, typebase *type)
{
    if (_types.count(name)) return false;
    _types[name] = type;
    return true;
}