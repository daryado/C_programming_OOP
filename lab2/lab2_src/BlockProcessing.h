#pragma once
#include <map>

#ifndef BLOCKPROCESSING_H
#define BLOCKPROCESSING_H

class BlockProcessing
{
protected:
	Words::Keywords lastKeyword;
	std::string BlockName;
	WorkBlock::Block currBlock;
	bool Completed;
public:
	BlockProcessing() : currBlock(WorkBlock::Block()), lastKeyword(Words::Keywords::NO_KEYWORD), Completed(false) {};

	virtual void Update(const std::string& word, Words::Keywords key, std::map <std::string, WorkBlock::Block>) {};


	void setLastKeyword(const Words::Keywords key) { lastKeyword = key; };
	void setCurrBlockName(const std::string& name) { BlockName = name; };
	void setCurrBlock(const WorkBlock::Block& block) { currBlock = block; };
    virtual bool correct() const {};

	const Words::Keywords& getlastKeyword() const { return lastKeyword; };
	const WorkBlock::Block& getCurrBlock() const { return currBlock; };
	const std::string& getCurrBlockName() const { return BlockName; };
};

class WorkflowBlockProcessing : public BlockProcessing
{
public:
	void Update(const std::string& word, Words::Keywords key, std::map <std::string, WorkBlock::Block>);
	bool correct() const;
};

#endif // !BLOCKPROCESSING_H