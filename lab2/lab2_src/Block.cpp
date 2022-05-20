#include "Block.h"

size_t WorkBlock::Block::ArgSize(const std::string word)
{
	using namespace WorkBlock;

	if ((word == "readfile") || (word == "writefile") || (word == "dump") || (word == "grep")) {
		return 1;
	}
	if (word == "replace") {
		return 2;
	}
		return 0;
}
