#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __DOCUMENT_TYPE_HPP
#define __DOCUMENT_TYPE_HPP

#include <string>

#include <lesslang/types/runtime/scope.hpp>
#include <lesslang/types/typecheck/typebase.hpp>

namespace lesslang::types::runtime
{
    class document final
    {
    private:
        scope _root;
        std::string _name;
    public:
        typecheck::typebase * type(std::string id);

        const variable var(std::string id);

        object * get(std::string id);
        bool set(std::string id, object *value);

        scope * root();
        scope * resolve(std::string id);

        bool import(document *doc);
        bool import(document *doc, std::string as);

        object * solve(std::string expr);

        inline document(std::string name) :
            _root(name, nullptr),
            _name(name)
        {
        }
    };
}

#endif