#include "Parser.h"
#include "Validator.h"
#include "definitions.h"
#include "BlockProcessing.h"


void WorkflowBlockProcessing::Update(const std::string& word, Words::Keywords key, std::map <std::string, WorkBlock::Block> blockTable)
{
	using namespace Words;

	if (key == Keywords::ARGS_OR_NUMBER) {
		if (currBlock.getArgs().size() < WorkBlock::Block::ArgSize(currBlock.getBlockName()))
			key = Keywords::BLOCK_ARGS;
		else 
			key = Keywords::BLOCK_NUMBER;
	}
    if (key == Keywords::DESC){
        if (lastKeyword != Keywords::NO_KEYWORD)
            throw Exceptions::Keyword_order_error(Keywords_str(lastKeyword), Keywords_str(key));
        BlockProcessing::currBlock.SetArgs({});
        currBlock.setName(definitions::no_name);
        BlockName.clear();
    }

	if (key == Keywords::CSED) {
		if (lastKeyword == Keywords::NO_KEYWORD || lastKeyword == Keywords::DESC || lastKeyword == Keywords::BLOCK_ARGS || lastKeyword == Keywords::BLOCK_NAME){
            BlockProcessing::currBlock.SetArgs({});
            currBlock.setName(definitions::no_name);
            BlockName.clear();
		}
		else
			throw Exceptions::Keyword_order_error(Keywords_str(lastKeyword), Keywords_str(key));
	}
	if (key == Keywords::BLOCK_NUMBER) {
		if (lastKeyword == Keywords::BLOCK_NAME || lastKeyword == Keywords::ASSIGN)
			throw Exceptions::Keyword_order_error(Keywords_str(lastKeyword), Keywords_str(key));
		BlockName = word;
		currBlock.SetArgs({});
	}
	
	if (key == Keywords::BLOCK_NAME) {
		if (lastKeyword != Keywords::ASSIGN)
			throw Exceptions::Keyword_order_error(Keywords_str(lastKeyword), Keywords_str(key));
		currBlock.setName(word);
	}
	if (key == Keywords::BLOCK_ARGS) {
		if (lastKeyword == Keywords::BLOCK_NAME || lastKeyword == Keywords::BLOCK_ARGS){
            currBlock.AddArgument(word);
		}
		else throw Exceptions::Keyword_order_error(Keywords_str(lastKeyword), Keywords_str(key));
	}
	if (key == Keywords::WRONG_KEYWORD|| key == Keywords::NO_KEYWORD) {
		throw Exceptions::Bad_keyword_error(Keywords_str(key));//

	}

	Completed = currBlock.getArgs().size() == currBlock.ArgSize(currBlock.getBlockName());
	lastKeyword = key;
}

bool WorkflowBlockProcessing::correct() const
{
	return lastKeyword == Words::Keywords::BLOCK_NUMBER || lastKeyword == Words::Keywords::CSED || lastKeyword == Words::Keywords::NO_KEYWORD;
}