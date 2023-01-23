#include <lesslang/types/runtime/primitives/dictionary.hpp>
#include <lesslang/types/runtime/primitives/string.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <lesslang.hpp>

#include <stdio.h>

using namespace lesslang::types::runtime::primitives;
using namespace lesslang::types::runtime;
using namespace lesslang::types::typecheck;

#pragma region TYPE
object * dict_type::typeInfo() { return nullptr; }
bool dict_type::check(object *value, bool first) const
{
    auto *type = value->type();
    if (type->spec() != type_t::TYPE || type->id() != DICT_TYPEID) return false;
    auto map = ((dict_obj *)value)->value();

#ifdef __USE_BOOST__
    BOOST_FOREACH(const auto& pair, map)
#else
    for(const auto& pair: map)
#endif
    {
        if (_typeMap.find(pair.first) == _typeMap.end()) return false;
        if(!_typeMap.at(pair.first)->check(pair.second, first)) return false;
    }

    return _typeMap.size() == map.size();
}
uint32_t dict_type::id() const { return DICT_TYPEID; }

makeResult_t dict_type::make(std::string name) 
{
    return makeResult_t {
        .success = true,
        .result = variable(name, this)
    };
}
makeResult_t dict_type::make(std::string name, std::vector<typebase*>)
{
    return makeResult_t { .success = false, .result = variable(std::string(nullptr), nullptr) };
}
dict_type *dict_type_inst = nullptr;
dict_type * LESSLANG_dict_type_instance()
{
    if (dict_type_inst) return dict_type_inst;
    dict_type_inst = new dict_type();
    return dict_type_inst;
}
dict_type * dict_type::instance()
{
    return LESSLANG_dict_type_instance();
}
#pragma endregion

#pragma region OBJECT
dict_obj::dict_obj(dictValue_t value) : object(LESSLANG_dict_type_instance()), _value(value)
{
}
object * dict_obj::applyOperator(std::string op, object *right) const
{
    return nullptr;
}
object * dict_obj::get(std::string name) const
{
    if (this->_value.find(name) == this->_value.end()) return nullptr;
    return this->_value.at(name);
}
bool dict_obj::set(std::string name, object *value)
{
    if (_type->id() != DICT_TYPEID || _type->spec() != type_t::TYPE) return false;
    auto type = ((dict_type *)_type);

    if (!type->_typeMap.count(name) || !type->_typeMap.at(name)->check(value)) return false;

    if (!this->_value.count(name)) this->_value.insert({name, value});
    else this->_value[name] = value;

    return true;
}
object * dict_obj::call(object *super, std::vector<object *> args) const
{
    return nullptr;
}
std::string dict_obj::represent() const
{
    std::stringstream _result;
    _result << "{ ";
    
#ifdef __USE_BOOST__
    BOOST_FOREACH(const auto& obj, this->_value)
#else
    for(const auto& obj : this->_value)
#endif
    {
        _result << obj.first << ": " << obj.second->represent() << ", ";
    }
    _result << "\b\b }";
    return _result.str();
}
std::vector<std::string> dict_obj::children() const
{
    std::vector<std::string> _result = std::vector<std::string>();
    
#ifdef __USE_BOOST__
    BOOST_FOREACH(const auto& pair, this->_value)
#else    
    for (const auto& pair : this->_value)
#endif
    {
        _result.push_back(pair.first);
    }
    
    return _result;
}
#pragma endregion