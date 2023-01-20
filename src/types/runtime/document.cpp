#include <lesslang/types/runtime/document.hpp>

#include <tuple>

using namespace std;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

tuple<scope *, string> access_scope(scope *root, string id)
{
    scope *curr = root;

    size_t x = 0;
    size_t c = 0;
    while ((c = id.find(':', x)) != -1)
    {
        auto rid = id.substr(x, c-x);
        curr = curr->getChild(rid);
        if (curr == nullptr) return { nullptr, string() };
        x = c+1;
    }

    return { curr, id.substr(x) };
}
object * get_object_property(scope *root, string id)
{
    object *curr = nullptr;

    size_t x = 0;
    size_t c = 0;
    while ((c = id.find('.', x)) != -1)
    {
        auto rid = id.substr(x, c-x);
        
        if (!curr) curr = root->getGlobal(rid);
        else curr = curr->get(rid);
        
        if (curr == nullptr) return nullptr;
        x = c+1;
    }

    if (!curr) return root->getGlobal(id);
    else return curr->get(id.substr(x));
}
bool set_object_property(scope *root, string id, object *value)
{
    object *curr = nullptr;
    typebase *type = nullptr;

    size_t x = 0;
    size_t c = 0;
    while ((c = id.find('.', x)) != -1)
    {
        auto rid = id.substr(x, c-x);
        
        if (!curr) curr = root->getGlobal(rid);
        else curr = curr->get(rid);

        if (curr == nullptr) return false;
        x = c+1;
    }
    
    if (!curr) return root->setGlobal(id, value);
    else return curr->set(id.substr(x), value);
}

typebase * document::type(string id)
{
    auto [scope, name] = access_scope(&_root, id);
    
    if (!scope) return nullptr;
    return scope->getType(name);
}

const variable document::var(string id)
{
    auto [scope, varname] = access_scope(&_root, id);

    if (!scope || !scope->_globals.count(varname)) return variable();
    return scope->_globals[varname];
}

object * document::get(string id)
{
    auto [scope, varname] = access_scope(&_root, id);

    if (!scope) return nullptr;
    
    return get_object_property(scope, varname);
}
bool document::set(string id, object *value)
{
    auto [scope, varname] = access_scope(&_root, id);

    if (!scope) return false;

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
    if (_root._children.count(doc->_root._name)) return false;
    
    _root._children[doc->_root._name] = doc->_root;
    return true;
}
bool document::import(document *doc, string as)
{
    if (_root._children.count(as)) return false;
    
    _root._children[as] = doc->_root;
    return true;
}