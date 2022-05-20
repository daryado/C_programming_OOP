#pragma once
#include <string>
#include <vector>
#include "WorkerBase.h"

#ifndef WORKERS_H
#define WORKERS_H


class BlockReadfile : public WorkerBase
{
public:
	BlockReadfile(const std::vector<std::string>& args, WorkerBase* const LastWorker = nullptr) : WorkerBase(args, LastWorker) {};
	void execute();
};


class BlockWritefile : public WorkerBase
{
public:
	BlockWritefile(const std::vector<std::string>& args, WorkerBase* const LastWorker = nullptr) : WorkerBase(args, LastWorker) {};
	void execute();
};


class BlockDump : public WorkerBase
{
public:
	BlockDump(const std::vector<std::string>& args, WorkerBase* const LastWorker = nullptr) : WorkerBase(args, LastWorker) {};
	void execute();
};


class BlockSort : public WorkerBase
{
public:
	BlockSort(WorkerBase* const prevUnit = nullptr) : WorkerBase({}, prevUnit) {};
	BlockSort(const std::vector<std::string>& args = {}, WorkerBase* const LastWorker = nullptr) : WorkerBase(args, LastWorker) {};
	void execute();
};


class BlockGrep : public WorkerBase
{
public:
	BlockGrep(const std::vector<std::string>& args, WorkerBase* const LastWorker = nullptr) : WorkerBase(args, LastWorker) {};
	void execute();
};


class BlockReplace : public WorkerBase
{
public:
	BlockReplace(const std::vector<std::string>& args, WorkerBase* const LastWorker = nullptr) : WorkerBase(args, LastWorker) {};
	void execute();
};

#endif // !WORKERS_H