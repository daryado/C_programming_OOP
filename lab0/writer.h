#ifndef LAB0_WRITER_H
#define LAB0_WRITER_H
#include <iostream>
#include <fstream>
#include <map>

namespace Writer
{
    void CSVwriter(std::multimap<int, std::string> count_words, long length, std::ofstream& out);
}

#endif //LAB0_WRITER_H
