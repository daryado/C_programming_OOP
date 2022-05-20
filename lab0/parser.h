#ifndef LAB0_PARSER_H
#define LAB0_PARSER_H
#include <iostream>
#include <map>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>

namespace pars {
    class Parser {
    private:
        long Length = 0;
    public:
        void StrTolower(std::string *str)
        {
            std::transform(str->begin(), str->end(), str->begin(),
            [](unsigned char c){ return (isalpha(c)||isdigit(c))? std::tolower(c) : ' '; });
        }

        long WordCount()
        {
            return Length;
        }

        std::multimap<int, std::string> StrParser(std::string str) {
            std::istringstream ss(str);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;

            std::map<std::string, int> word_count;
            std::for_each(begin, end, [&](const std::string &s) {
                ++word_count[s];
                ++Length;
            });

            std::multimap<int, std::string> count_words;
            for (auto it = word_count.begin(); it != word_count.end();++it){
                count_words.insert(std::make_pair(it->second, it->first));
            }
            return count_words;
        }

    };

#endif //LAB0_PARSER_H
}
