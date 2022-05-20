#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <vector>
#include "Workers.h"
#include "WorkerBase.h"

class ExecuteWorkers
{
public:
	ExecuteWorkers() {};
	virtual void exec() {};
	virtual void reset() {};
};

class WorkflowExecutor : public ExecuteWorkers
{
private:
	const std::vector<WorkerBase*>& workers_;
public:
	WorkflowExecutor(const std::vector<WorkerBase*>& w) : workers_(w) {};
	void exec();

	void deleteWorkers();
};

#endif // !EXECUTOR_H
