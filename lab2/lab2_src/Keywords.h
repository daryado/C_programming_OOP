#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <string>
#include <iostream>

namespace Words
{
	enum class Keywords
	{
		DESC,
		CSED,
		ASSIGN,
		NEXT,
		BLOCK_NUMBER,
		BLOCK_NAME,
		BLOCK_ARGS,
		WRONG_KEYWORD,
		NO_KEYWORD,
		ARGS_OR_NUMBER
	};

	std::string Keywords_str(const Keywords& key);
	Keywords Str_keywords(const std::string& word);
}

#endif // !KEYWORDS_H
