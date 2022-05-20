#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Block.h"
#include "Keywords.h"
#include "BlockProcessing.h"
#include "WorkerBase.h"
#include "Workers.h"

namespace Pars
{
	class Parser
	{
	protected:
		std::map <std::string, WorkBlock::Block> blockTable;
		std::vector<WorkBlock::Block> queue;
		std::vector<WorkerBase*> WorkerQueue;
	public:
        Parser() {};
		virtual void run( BlockProcessing& processing) {};
		virtual void ConnectWorkers() {};
		virtual void deleteConnectWorkers() {};

		const std::map <std::string, WorkBlock::Block>& getBlockTable() const { return blockTable; };
		std::vector<WorkBlock::Block> getQueue() { return queue; };
		std::vector<WorkerBase*> getWorkerQueue() const { return WorkerQueue; };

	};

	class WorkflowParser : public Parser
	{
	private:
		std::string fileName;

		void ReadingProcessing(std::ifstream& fin, WorkflowBlockProcessing& processing);
	public:
		WorkflowParser() : Parser() {};
		WorkflowParser(const std::string& fileName_) : Parser(), fileName(fileName_) {};

		void MapDefinition(std::map<std::string, std::function<WorkerBase* (WorkBlock::Block block_)>> &workers);
		void run( WorkflowBlockProcessing& processing);

		void ConnectWorkers();
		void deleteConnectWorkers();
	};
}

#endif // !PARSER_H