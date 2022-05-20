#include "Workers.h"
#include "Executor.h"
#include "Validator.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>


void BlockReadfile::execute()
{
    try
    {
        if (args.size() < 1)
            throw Exceptions::BadArguments("No input file name in readunit");
        drop();
        const std::string file = args[0];

        std::ifstream in(file);
        if (!in.is_open())
            throw Exceptions::File_Error("Can't open file to read " + file);

        std::string line;

        while (getline(in, line)) {
            if (in.fail())
                throw Exceptions::File_Error("Can't read from file " + file);
            output.push_back(line);
        }

        in.close();
    }
    catch (std::exception e)
    {
        throw e.what();
    }
}

void BlockWritefile::execute()
{
    try
    {
        if (args.size() < 1)
            throw Exceptions::BadArguments("No input file name in readunit");
        drop();
        const std::string file = args[0];
        std::ofstream out(file);
        if (LastWorker)
            input = LastWorker->getOutput();

        if (!out.is_open())
            throw Exceptions::File_Error("Can't open file to read " + file);

        for (const auto& part : input) {
            out << part << std::endl;
            if (out.fail())
                throw Exceptions::File_Error("Can't read from file " + file);
        }

        out.close();
    }
    catch (std::exception e)
    {
        throw e.what();
    }
}

void BlockDump::execute()
{
    try
    {
        if (!args.size())
            throw Exceptions::BadArguments("No input file name in readunit");
        drop();

        const std::string file = args[0];
        std::ofstream out(file);

        if (LastWorker)
            input = LastWorker->getOutput();

        for (const auto& part : input) {
            out << part << std::endl;
            output.push_back(part);
            if (out.fail())
                throw Exceptions::File_Error("Can't read from file " + file);
        }
        out.close();
    }
    catch (std::exception e)
    {
        throw e.what();
    }
}

void BlockSort::execute()
{
    drop();
    if (LastWorker)
        input = LastWorker->getOutput();
    output = input;
    std::sort(output.begin(), output.end()); 
}

void BlockGrep::execute()
{
    try
    {
        if (!args.size())
            throw Exceptions::BadArguments("No input file name in readunit");
        drop();

        const std::string word = args[0];

        if (LastWorker)
            input = LastWorker->getOutput();

        for (const auto& part : input) {
            if (part.find(word) != std::string::npos) {
                output.push_back(part);
            }
        }
    }
    catch (std::exception e)
    {
    throw e.what();
    }
}

void BlockReplace::execute()
{
    try
    {
        if (!args.size())
            throw Exceptions::BadArguments("No input file name");
        drop();

        if (LastWorker)
            input = LastWorker->getOutput();
        const std::string word1 = args[0];
        const std::string word2 = args[1];
        size_t i;
        size_t len = word1.length();
        std::string in;
        for (auto& part : input) {
            std::string s = part;
            std::string out = "";
            while ((i = s.find(word1)) != s.npos) {
                std::string sub = s.substr(0, i + len);
                s.replace(i, len, word2);
                out += s.substr(0, i + word2.length());
                s.erase(0, i + word2.length());
            }
            out += s;
            output.push_back(out);
        }
    }
    catch (std::exception e)
    {
        throw e.what();
    }
}
