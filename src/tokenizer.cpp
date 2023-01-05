#include <lesslang/tokenizer.hpp>

using namespace lesslang;
using namespace std;

vector<tuple<tokenizer::operator_t, string>> tokenizer::tokenizeType(string type)
{
    vector<tuple<operator_t, string>> result = vector<tuple<operator_t, string>>();

    operator_t op = {0};
    string temp = "";

    for (auto c : type)
    {
        if (c == tokens::operators::bitwise::_or)
        {
            if (!temp.empty())
            {
                result.push_back({op, temp});
                temp.clear();
            }
            op.type = 1;
        }
        else if (
            c == tokens::white::newline ||
            c == tokens::white::ret ||
            c == tokens::white::space ||
            c == tokens::white::tab
        )
        {
            if (!temp.empty())
            {
                result.push_back({op, temp});
                temp.clear();
                op.type = 0;
            }
        }
        else if (c == tokens::operators::logical::negate && type.empty()) op.negate = true;
        else temp += c;
    }
    if (!temp.empty()) result.push_back({op, temp});
    
    return result;
}