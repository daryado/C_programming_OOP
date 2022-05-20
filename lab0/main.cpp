#include "parser.h"
#include "writer.h"
#include <iostream>
#define INPUT_N 1
#define OUTPUT_N 2

int main(int argc, char** argv){
    std::ifstream file_in(argv[INPUT_N]);

        if (!file_in){
           std::cout << "The file input.txt was not open"<<std::endl;
           return 0;
        }
    std::string Line;
    std::copy(std::istreambuf_iterator<char>(file_in), std::istreambuf_iterator<char>(),
              std::back_inserter(Line));
    pars::Parser MyParser;
    MyParser.StrTolower(&Line);
    std::multimap<int, std::string> words = MyParser.StrParser(Line);
    std::ofstream file_out(argv[INPUT_N]);
    Writer::CSVwriter(words, MyParser.WordCount(), file_out);
    return 0;
}

