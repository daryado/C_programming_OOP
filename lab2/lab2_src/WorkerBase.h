#ifndef WORKERBASE_H
#define WORKERBASE_H

#include <string>
#include <vector>


class WorkerBase
{
protected:
	std::vector<std::string> input;
	std::vector<std::string> output;
	std::vector<std::string> args;
    WorkerBase* LastWorker;
public:
	WorkerBase(const std::vector<std::string>& args, WorkerBase* const LastWorker= nullptr) : args(std::vector<std::string>(args)), LastWorker(LastWorker) {};

	virtual void execute(){if (LastWorker != nullptr) input = LastWorker->getOutput(); output = input;};

	const std::vector<std::string>& getOutput() const { return output; };
	void setLast(WorkerBase* const Last = nullptr) { this->LastWorker = Last; };

	void drop()
	{
		input.clear();
		output.clear();
	}

};


#endif // !WORKERBASE_H