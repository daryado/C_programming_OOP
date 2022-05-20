#include "Keywords.h"
#include "definitions.h"

std::string Words::Keywords_str(const Keywords& key)
{
	using namespace definitions;

	if (key == Keywords::DESC)
		return desc;

	if (key == Keywords::CSED)
		return csed;

	if (key == Keywords::BLOCK_NUMBER)
		return block_number;

	if (key == Keywords::BLOCK_NAME)
		return block_name;

	if (key == Keywords::BLOCK_ARGS)
		return block_args;

	if (key == Keywords::NEXT)
		return next;

	if (key == Keywords::ASSIGN)
		return assign;

	if (key == Keywords::WRONG_KEYWORD)
		return wrong_keyword;

	return no_keyword;
}

Words::Keywords Words::Str_keywords(const std::string& word)
{
	using namespace definitions;

	if (word == next)
		return Keywords::NEXT;

	if (word == assign)
		return Keywords::ASSIGN;

	if ((word == readfile) || (word == writefile) || (word == grep) || (word == replace) || (word == sort) || (word == dump))
		return Keywords::BLOCK_NAME;

	if (word == desc)
		return Keywords::DESC;

	if (word == csed)
		return Keywords::CSED;


	return Keywords::ARGS_OR_NUMBER;
}
