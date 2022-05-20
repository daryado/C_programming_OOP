#include "Application.h"
#include "Parser.h"
#include "Executor.h"
#include "BlockProcessing.h"

void runWorkflowExecutor(const std::vector<std::string>& args)
{
    using namespace Pars;
    WorkflowParser parser = WorkflowParser(args[0]);
    WorkflowBlockProcessing proc;
    WorkflowParser(args[0]).run(proc);

	ExecuteWorkers executor = WorkflowExecutor(parser.getWorkerQueue());
	executor.exec();
}
