#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../../lab2_src/Block.h"
#include "../../lab2_src/Parser.h"
#include "../../lab2_src/Executor.h"
#include "../../lab2_src/Validator.h"
#include "../../lab2_src/BlockProcessing.h"
#include "../../lab2_src/Keywords.h"
#include "../../lab2_src/Application.h"
#include "../../lab2_src/WorkerBase.h"
#include "../../lab2_src/Workers.h"
#include "../../lab2_src/definitions.h"


const std::string fileName = "run_test.txt";
const std::string readFileName = "run_test_readfile.txt";
const std::string writeFileName = "run_test_writefile.txt";
const std::string dumpFileName = "run_test_dumpfile.txt";
const std::string grepWord = "probably";
const std::string replacementWord = "definitely";

const std::vector<std::string> fileContent =
        { "desc",
          "code1 = readfile " + readFileName,
          "code2 = writefile " + writeFileName,
          "code3 = grep " + grepWord,
          "code4 = sort",
          "code5 = dump " + dumpFileName,
          "code6 = replace " + grepWord + " " + replacementWord,
          "csed",
          "code1 -> code3 -> code6 -> code5 -> code4 -> code2" };

const std::vector<std::string> readFileContent =
        { "If you walk down the street and see someone throw"
          "a plastic bottle on the ground, yo u’ll probably get"
                "annoyed. You might even say something to that"
                "person. But do we react in the same way when we"
                "see people throwing rubbish into the sea? We all"
                "know how rubbish damages the environment on land,"
                "but we often forget the effect that it can have on"
                "environments like the sea, lakes and rivers, too." };

void createTestFile(const std::string& file, const std::vector<std::string>& content)
{
    std::ofstream fout(file);
    if (!fout.is_open())
        throw Exceptions::FileNotCreated(file);

    for (auto iter = content.cbegin(); iter != content.cend(); ++iter)
        fout << *iter << std::endl;

    fout.close();
}

TEST(IO, rdbuf)
{
using namespace std;
streambuf* buf;
buf = cin.rdbuf();

createTestFile("test.txt", { "hello" });
ifstream fin("test.txt");
cin.rdbuf(fin.rdbuf());

std::string word;
cin >> word;
EXPECT_EQ(word, "hello");
cin.rdbuf(buf);
}

TEST(Parser, run) {
using namespace Pars;
using namespace std;

WorkflowBlockProcessing processing;
ASSERT_NO_THROW(createTestFile(fileName, fileContent));
ASSERT_NO_THROW(createTestFile(readFileName, readFileContent));

Parser parser = WorkflowParser(fileName);

ASSERT_NO_THROW(parser.run(processing));
}

TEST(Analyzer, update)
{
    WorkflowBlockProcessing proc;
    std::map <std::string, WorkBlock::Block> blockTable;

    ASSERT_NO_THROW(proc.Update("desc", Words::Keywords::DESC, blockTable));
    ASSERT_NO_THROW(proc.Update("code1", Words::Keywords::ARGS_OR_NUMBER, blockTable));
    ASSERT_NO_THROW(proc.Update("=", Words::Keywords::ASSIGN, blockTable));
    ASSERT_NO_THROW(proc.Update("replace", Words::Keywords::BLOCK_NAME, blockTable));
    ASSERT_NO_THROW(proc.Update("word1", Words::Keywords::ARGS_OR_NUMBER, blockTable));
    ASSERT_NO_THROW(proc.Update("word2", Words::Keywords::ARGS_OR_NUMBER, blockTable));

    EXPECT_EQ(proc.getCurrBlock().getArgs().size(), 2);
    EXPECT_EQ(proc.getCurrBlock().getArgs()[0], "word1");
    EXPECT_EQ(proc.getCurrBlock().getArgs()[1], "word2");
    EXPECT_EQ(proc.getCurrBlock().getBlockName(), definitions::replace);

    ASSERT_NO_THROW(proc.Update("csed", Words::Keywords::CSED, blockTable));
    EXPECT_EQ(proc.correct(), true);

    EXPECT_EQ(proc.getCurrBlock().getArgs().size(), 0);
    EXPECT_EQ(proc.getCurrBlock().getBlockName(), definitions::no_name);
}

TEST(Keywords, Str_keywords)
{

    BlockProcessing proc = WorkflowBlockProcessing();
    std::map <std::string, WorkBlock::Block> blockTable;
    EXPECT_EQ(Words::Str_keywords("desc"), Words::Keywords::DESC);
    ASSERT_NO_THROW(proc.Update("desc", Words::Keywords::DESC , blockTable));

    EXPECT_EQ(Words::Str_keywords("1"), Words::Keywords::ARGS_OR_NUMBER);
    ASSERT_NO_THROW(proc.Update("1", Words::Keywords::ARGS_OR_NUMBER, blockTable));

    EXPECT_EQ(Words::Str_keywords("="), Words::Keywords::ASSIGN);
    ASSERT_NO_THROW(proc.Update("=", Words::Keywords::ASSIGN, blockTable));

    EXPECT_EQ(Words::Str_keywords("replace"), Words::Keywords::BLOCK_NAME);
    ASSERT_NO_THROW(proc.Update("replace", Words::Keywords::BLOCK_NAME, blockTable));

    EXPECT_EQ(Words::Str_keywords("w"), Words::Keywords::ARGS_OR_NUMBER);
    ASSERT_NO_THROW(proc.Update("w", Words::Keywords::ARGS_OR_NUMBER, blockTable));

    EXPECT_EQ(Words::Str_keywords("b"), Words::Keywords::ARGS_OR_NUMBER);
    ASSERT_NO_THROW(proc.Update("b", Words::Keywords::ARGS_OR_NUMBER, blockTable));

    EXPECT_EQ(Words::Str_keywords("csed"), Words::Keywords::CSED);
    ASSERT_NO_THROW(proc.Update("csed", Words::Keywords::CSED, blockTable));

    EXPECT_EQ(Words::Str_keywords("d567"), Words::Keywords::ARGS_OR_NUMBER);
    ASSERT_NO_THROW(proc.Update("d567", Words::Keywords::ARGS_OR_NUMBER, blockTable));

    EXPECT_EQ(Words::Str_keywords("->"), Words::Keywords::NEXT);
    ASSERT_NO_THROW(proc.Update("->", Words::Keywords::NEXT, blockTable));

}

TEST(Unit, readUnit_execute)
{
    std::string fileName = "unit_readfile.txt";
    std::vector<std::string> content =
            {
                    "123",
                    "234",
                    "345"
            };

    createTestFile(fileName, content);

    auto Worker = BlockReadfile({ fileName });
    ASSERT_NO_THROW(Worker.execute());

    EXPECT_EQ(Worker.getOutput()[0], "123");
    EXPECT_EQ(Worker.getOutput()[1], "234");
    EXPECT_EQ(Worker.getOutput()[2], "345");

}

TEST(Unit, unit_execute)
{
    std::string fileName = "block.txt";
    std::vector<std::string> content =
            {
                    "123",
                    "234",
                    "345"
            };

    createTestFile(fileName, content);
    BlockReadfile Read = BlockReadfile({fileName});
    Read.execute();

    auto workerBase = WorkerBase({}, &Read);
    workerBase.execute();

    EXPECT_EQ(workerBase.getOutput()[0], "123");
    EXPECT_EQ(workerBase.getOutput()[1], "234");
    EXPECT_EQ(workerBase.getOutput()[2], "345");
}

TEST(Unit, grepUnit_execute)
{
    std::string fileName = "grep.txt";
    std::vector<std::string> content =
            {
                    "123",
                    "234",
                    "345"
            };

    createTestFile(fileName, content);
    BlockReadfile Read = BlockReadfile({fileName});
    Read.execute();

    auto grep = BlockGrep({"123" }, &Read);
    ASSERT_NO_THROW(grep.execute());

    EXPECT_EQ(grep.getOutput().size(), 1);
    EXPECT_EQ(grep.getOutput()[0], "123");
}

TEST(Unit, sort)
{
    std::string fileName = "unit_sort.txt";
    std::vector<std::string> content =
            {
                    "345",
                    "234",
                    "11",
                    "1",
                    "123"
            };

    createTestFile(fileName, content);

    BlockReadfile Read = BlockReadfile({fileName});
    Read.execute();

    auto sort = BlockSort(&Read);
    ASSERT_NO_THROW(sort.execute());
    EXPECT_EQ(sort.getOutput().size(), 5);

    EXPECT_EQ(sort.getOutput()[0], "1");
    EXPECT_EQ(sort.getOutput()[1], "11");
    EXPECT_EQ(sort.getOutput()[2], "123");
    EXPECT_EQ(sort.getOutput()[3], "234");
    EXPECT_EQ(sort.getOutput()[4], "345");
}

TEST(Unit, replace)
{
    std::string fileName = "replace.txt";
    std::vector<std::string> content =
            {
                    "123",
                    "234",
                    "345"
            };

    createTestFile(fileName, content);

    BlockReadfile Read = BlockReadfile({fileName});
    Read.execute();

    auto replace = BlockReplace({"3", "33" }, &Read);
    ASSERT_NO_THROW(replace.execute());

    EXPECT_EQ(replace.getOutput().size(), 3);

    EXPECT_EQ(replace.getOutput()[0], "1233");
    EXPECT_EQ(replace.getOutput()[1], "2334");
    EXPECT_EQ(replace.getOutput()[2], "3345");
}

TEST(Executor, run)
{
    std::string fileName2 = "in.txt";
    std::vector<std::string> content2 =
            {
                    "345",
                    "234",
                    "123",
                    "12",
                    "11",
                    "1"
            };

    createTestFile(fileName2, content2);

    std::string fileName1 = "workflow.txt";
    std::vector<std::string> content1 =
            {
                    "desc\n"
                    "0 = readfile in.txt\n"
                    "2 = grep 3\n"
                    "1 = replace 2 4\n"
                    "3 = sort\n"
                    "csed\n"
                    "0 -> 1 -> 2 -> 3 \n"
            };

    createTestFile(fileName1, content1);
    const std::vector<WorkBlock::Block> blocks =
            {
                    {definitions::readfile, {fileName}},
                    {definitions::grep, {"1"}},
                    {definitions::sort, {}},
                    {definitions::dump, {"executor_output.txt"}}
            };

    using namespace Pars;
    WorkflowParser parser = WorkflowParser(fileName1);
    parser.getQueue() = blocks;
    parser.ConnectWorkers();

    auto executor = WorkflowExecutor(parser.getWorkerQueue());
    ASSERT_NO_THROW(executor.exec());
}