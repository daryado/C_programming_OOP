#include "Validator.h"
#include "Executor.h"

void WorkflowExecutor::exec()
{
	try
	{
		for (const auto& part : workers_) {
			part->execute();
		}
	}
	catch (std::exception e)
	{
		deleteWorkers();
		throw e;
	}
}

void WorkflowExecutor::deleteWorkers()
{
	for (const auto& part : workers_) {
		part->drop();
	}
}
