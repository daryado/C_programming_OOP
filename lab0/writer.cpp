#include "writer.h"
#include "parser.h"

namespace Writer {
    void CSVwriter(std::multimap<int, std::string> count_words,long length, std::ofstream& out) {

        if (!out){
            std::cout <<"The file output.csv was not open"<<std::endl;
            return;
        }

        out <<  "Word;Frequency;Frequency (%);" << "\n";

        for (auto it = count_words.rbegin(); it != count_words.rend(); ++it){
            out << it->second << ";" << it->first << ";" << it->first*100/length<< "% ;" << "\n";
        }
    }
}

