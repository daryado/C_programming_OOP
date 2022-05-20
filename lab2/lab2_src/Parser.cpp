#include <istream>
#include <fstream>
#include <locale>
#include "Parser.h"
#include "BlockProcessing.h"
#include "Validator.h"
#include "definitions.h"
#include "Keywords.h"
#include "Block.h"
#include "Workers.h"


void Pars::WorkflowParser::ReadingProcessing(std::ifstream& in, WorkflowBlockProcessing& processing)
{
	using namespace std;
	using namespace Pars;
	using namespace Exceptions;

	try
	{
		string word;
		if (in.fail())
			throw File_Error(fileName);

		bool csed_found = false;
		bool BlockDone = false;
		while (!csed_found)
		{
			if (in.eof())
				throw EOF_Error(fileName);
			in >> word;

			if (in.fail())
				throw File_Error(fileName);

			Words::Keywords key = Words::Str_keywords(word);
			WorkBlock::Block CurrBlock;
			
			processing.Update(word, key, blockTable);

			CurrBlock = processing.getCurrBlock();
			BlockDone = CurrBlock.getArgs().size() == CurrBlock.ArgSize(CurrBlock.getBlockName());
            if (BlockDone){
                    if(blockTable.find(processing.getCurrBlockName()) != blockTable.end())
                        throw Exceptions::BlockRedefinition(processing.getCurrBlockName());
                    blockTable[processing.getCurrBlockName()] = CurrBlock;
            }
			csed_found = key == Words::Keywords::CSED;
		}

		while (in >> word)
		{
			Words::Keywords key = Words::Str_keywords(word);

			processing.Update(word, key, blockTable);
			if (key == Words::Keywords::BLOCK_NUMBER) {
				if (blockTable.find(word) == blockTable.end())
					throw BlockNotDefined(word);
				queue.push_back(blockTable[word]);
                continue;
			}
		}
		if (!processing.correct())
			throw EOF_Error(fileName);
	}
	catch (std::exception e)
	{
		throw e.what();
	}
}

void Pars::WorkflowParser::run(WorkflowBlockProcessing& processing)
{
		std::ifstream in(fileName);

		ReadingProcessing(in, processing);

		in.close();

		ConnectWorkers();
}

void Pars::WorkflowParser::MapDefinition(std::map<std::string, std::function<WorkerBase*(WorkBlock::Block block_)>>& workers) {

	workers[definitions::dump] = [](WorkBlock::Block block_) { return new BlockDump(block_.getArgs()); };
	workers[definitions::writefile] = [](WorkBlock::Block block_) { return new BlockWritefile(block_.getArgs()); };
	workers[definitions::readfile] = [](WorkBlock::Block block_) { return new BlockReadfile(block_.getArgs()); };
	workers[definitions::sort] = [](WorkBlock::Block block_) { return new BlockSort(block_.getArgs()); };
	workers[definitions::grep] = [](WorkBlock::Block block_) { return new BlockGrep(block_.getArgs()); };
	workers[definitions::replace] = [](WorkBlock::Block block_) { return new BlockReplace(block_.getArgs()); };

}

void Pars::WorkflowParser::ConnectWorkers()
{
	using namespace WorkBlock;

	WorkerBase* lastWorker = nullptr;
	std::map<std::string, std::function<WorkerBase*(WorkBlock::Block block_)>> workers;

	MapDefinition(workers);

	for (const auto& part : queue)
	{
		WorkerBase* worker_;
		worker_ = workers[part.getBlockName()](part);

		worker_->setLast(lastWorker);
		lastWorker = worker_;

		WorkerQueue.push_back(worker_);
	}
}

void Pars::WorkflowParser::deleteConnectWorkers()
{
	for (const auto& part : WorkerQueue)
	{
		delete part;
	}
}
