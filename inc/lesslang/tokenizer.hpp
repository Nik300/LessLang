#ifndef __cplusplus
#error Lesslang library is cpp-only
#endif

#ifndef __TOKENIZER_COMPONENT_HPP
#define __TOKENIZER_COMPONENT_HPP

#include <vector>
#include <string>
#include <tuple>
#include <stdint.h>

namespace lesslang
{
    namespace tokens
    {
        enum class type
        {
            Expression,
            Declaration

        };
        namespace white
        {
            constexpr char newline = '\n';
            constexpr char space   = ' ';
            constexpr char tab     = '\t';
            constexpr char ret     = '\r';
        }
        namespace flow
        {
            constexpr char endOfStatement = ';';
            constexpr char typeDeclarator = ':';
            constexpr char accessor = '.';
        }
        namespace brackets
        {
            namespace open
            {
                constexpr char round  = '(';
                constexpr char square = '[';
                constexpr char curly  = '{';
                constexpr char angle  = '<';
            }
            namespace close
            {
                constexpr char round = ')';
                constexpr char square = ']';
                constexpr char curly = '}';
                constexpr char angle = '>';
            }
        }
        namespace operators
        {
            namespace arithmetic
            {
                constexpr char addition = '+';
                constexpr char subtraction = '-';
                constexpr char division = '/';
                constexpr char multiplication = '*';
                constexpr char modulo = '%';
            }
            namespace bitwise
            {
                constexpr char *rshift = ">>";
                constexpr char *lshift = "<<";
                constexpr char _and = '&';
                constexpr char _or = '|';
                constexpr char _xor = '^';
                constexpr char _compl = '~';
            }
            namespace assignment
            {
                constexpr char assign = '=';
                constexpr char *addition = "+=";
                constexpr char *subtraction = "-=";
                constexpr char *division = "/=";
                constexpr char *multiplication = "*=";
                constexpr char *modulo = "%=";
                constexpr char *null = "?=";
            }
            namespace logical
            {
                constexpr char *equals = "==";
                constexpr char *differs = "!=";
                constexpr char *grater = ">";
                constexpr char *less = "<";
                constexpr char *ge = ">=";
                constexpr char *le = "<=";
                constexpr char negate = '!';
            }
        }
    }

    class tokenizer final
    {
    public:
        struct operator_t
        {
        public:
            uint8_t type : 7;
            bool negate : 1;
        };
    public:
        static std::vector<std::tuple<operator_t, std::string>> tokenizeType(std::string type);
    };
}


#endif